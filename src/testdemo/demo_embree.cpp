#include <eloimx/eloimx.h>

#include <embree3/rtcore.h>
#include <eloimx/render/perspective.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

void test() {
    // RTCDevice rtcNewDevice (const char *config)
    RTCDevice device = rtcNewDevice(nullptr);

    //std::cout << rtcGetDeviceProperty(device, RTC_DEVICE_PROPERTY_VERSION) << "\n";    

    //std::cout << rtcGetDeviceError(device) << "\n";

    RTCScene scene = rtcNewScene(device);
    
    

    RTCGeometry tri = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);
    
    // set the buffer : indices and vertexes

    float *vertices = (float *)rtcSetNewGeometryBuffer(
        tri,
        RTC_BUFFER_TYPE_VERTEX,
        0,
        RTC_FORMAT_FLOAT3,
        3*sizeof(float),
        4
    );

    unsigned *indices = (unsigned *)rtcSetNewGeometryBuffer(
        tri,
        RTC_BUFFER_TYPE_INDEX,
        0,
        RTC_FORMAT_UINT3,
        3*sizeof(unsigned),
        2
    );

    if(vertices && indices){
        vertices[0] = 1.f; vertices[1] = 1.f; vertices[2] = 2.0f;
        vertices[3] = -1.f; vertices[4] = 1.f; vertices[5] = 2.0f;
        vertices[6] = -1.f; vertices[7] = -1.f; vertices[8] = 2.0f;
        vertices[9] = 1.f; vertices[10] = -1.f; vertices[11] = 2.0f;

        indices[0] = 0; indices[1] = 1; indices[2] = 2;
        indices[3] = 0; indices[4] = 3; indices[5] = 2;
    }

    rtcCommitGeometry(tri);

    rtcAttachGeometry(scene, tri);

    rtcCommitScene(scene);

// intersect
/*
    rtcIntersect1(
        RTCScene scene,
        RTCIntersectContext *text,
        RTCRayHit *rayhit
    );
*/  

    eloimx::elxPerspectiveCamera camera;

    char color[100 * 100 * 3];    

    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            eloimx::elxRay ray;
            Point2f uv(j * 0.01f, i * 0.01f);
            camera.generateRay(ray, uv);

            RTCIntersectContext context;
            rtcInitIntersectContext(&context);
            RTCRayHit rayhit;

            rayhit.ray = ray.toRTC();

            rayhit.hit.geomID = RTC_INVALID_GEOMETRY_ID;
            rayhit.hit.instID[0] = RTC_INVALID_GEOMETRY_ID;

            rtcIntersect1(scene, &context, &rayhit);
            if(rayhit.hit.geomID != RTC_INVALID_GEOMETRY_ID) {
                color[i * 100 * 3 + j * 3] = 255 * i * 0.01;
                color[i * 100 * 3 + j * 3 + 1] = 255 * j * 0.01;
                color[i * 100 * 3 + j * 3 + 2] = 100;
            } else {
                color[i * 100 * 3 + j * 3] = 0;
                color[i * 100 * 3 + j * 3 + 1] = 0;
                color[i * 100 * 3 + j * 3 + 2] = 0;            
            }
        }
    }

    stbi_write_tga("demo2.tga", 100, 100, 3, color);


    // release the screen
    rtcReleaseScene(scene);

    // release the device
    rtcReleaseDevice(device);

}