#include <embree3/rtcore.h>
#include <stdio.h>
#include <limits>

#if defined(_WIN32)
#  include <conio.h>
#  include <windows.h>
#endif

void errorFunction(void *userPtr, enum RTCError error, const char *str) {
    printf("error %d: %s\n", error, str);
}

RTCDevice initDevice() {
    RTCDevice device = rtcNewDevice(NULL);

    if (!device) {
        printf("error %d: cannot create device\n", rtcGetDeviceError(NULL));
    }

    rtcSetDeviceErrorFunction(device, errorFunction, NULL);
    return device;
}

RTCScene initScene(RTCDevice device) {
    RTCScene scene = rtcNewScene(device);

    RTCGeometry geom = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);
    float *vertices = (float*) rtcSetNewGeometryBuffer(geom,
                                                       RTC_BUFFER_TYPE_VERTEX,
                                                       0,
                                                       RTC_FORMAT_FLOAT3,
                                                       3 * sizeof(float),
                                                       3);
    unsigned *indices = (unsigned*) rtcSetNewGeometryBuffer(geom,
                                                            RTC_BUFFER_TYPE_INDEX,
                                                            0,
                                                            RTC_FORMAT_UINT3,
                                                            3 * sizeof(unsigned),
                                                            1);
    
    if (vertices && indices) {
        vertices[0] = .0f; vertices[1] = .0f; vertices[2] = .0f;
        vertices[3] = 1.f; vertices[4] = 0.f; vertices[5] = .0f;
        vertices[6] = .0f; vertices[7] = 1.f; vertices[8] = .0f;

        indices[0] = 0; indices[1] = 1; indices[2] = 2;
    }

    rtcCommitGeometry(geom);
    rtcAttachGeometry(scene, geom);
    rtcReleaseGeometry(geom);

    rtcCommitScene(scene);
    return scene;
}

void castRay(RTCScene scene,
             float ox, float oy, float oz,
             float dx, float dy, float dz) {
    RTCIntersectContext context;
    rtcInitIntersectContext(&context);

    RTCRayHit rayHit;

    rayHit.ray.org_x = ox;
    rayHit.ray.org_y = oy;
    rayHit.ray.org_z = oz;
    rayHit.ray.dir_x = dx;
    rayHit.ray.dir_y = dy;
    rayHit.ray.dir_z = dz;
    rayHit.ray.tnear = 0;
    rayHit.ray.tfar = std::numeric_limits<float>::infinity();
    rayHit.ray.mask = -1;
    rayHit.ray.flags = 0;
    rayHit.hit.geomID = RTC_INVALID_GEOMETRY_ID;
    rayHit.hit.instID[0] = RTC_INVALID_GEOMETRY_ID;

    rtcIntersect1(scene, &context, &rayHit);

    printf("%.6f, %.6f, %.6f: \n",  ox, oy, oz);
    if (rayHit.hit.geomID != RTC_INVALID_GEOMETRY_ID) {
        printf("Found intersection on geometry %d, primitive %d at tfar = %.6f\n",
                rayHit.hit.geomID,
                rayHit.hit.primID,
                rayHit.ray.tfar);
    } else {
        printf("Did not find any intersection.\n");
    }
}

void waitForKeyPressedUnderWindows()
{
#if defined(_WIN32)
  HANDLE hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (!GetConsoleScreenBufferInfo(hStdOutput, &csbi)) {
    printf("GetConsoleScreenBufferInfo failed: %d\n", GetLastError());
    return;
  }
  
  /* do not pause when running on a shell */
  if (csbi.dwCursorPosition.X != 0 || csbi.dwCursorPosition.Y != 0)
    return;
  
  /* only pause if running in separate console window. */
  printf("\n\tPress any key to exit...\n");
  int ch = getch();
#endif
}

void test() {
    RTCDevice device = initDevice();
    RTCScene scene = initScene(device);

    castRay(scene, 0, 0, -1, 0, 0, 1);

    castRay(scene, 1, 1, -1, 0, 0, 1);

    rtcReleaseScene(scene);
    rtcReleaseDevice(device);

    waitForKeyPressedUnderWindows();
}