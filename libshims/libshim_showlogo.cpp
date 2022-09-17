#include <gui/SurfaceComposerClient.h>

using namespace android;

extern "C" {

void _ZN7android21SurfaceComposerClient13createSurfaceERKNS_7String8EjjijRKNS_2spINS_7IBinderEEENS_13LayerMetadataEPj(const String8& name, uint32_t w, uint32_t h, PixelFormat format, uint32_t flags, const sp<IBinder>& parentHandle, LayerMetadata metadata, uint32_t* outTransformHint);

void _ZN7android21SurfaceComposerClient13createSurfaceERKNS_7String8EjjijPNS_14SurfaceControlENS_13LayerMetadataEPj(const String8& name, uint32_t w, uint32_t h, PixelFormat format, uint32_t flags, SurfaceControl* parent, LayerMetadata metadata, uint32_t* outTransformHint) {
  _ZN7android21SurfaceComposerClient13createSurfaceERKNS_7String8EjjijRKNS_2spINS_7IBinderEEENS_13LayerMetadataEPj(name, w, h, format, flags, nullptr, metadata, nullptr);
 }

void _ZN7android14SurfaceControl10getSurfaceEv(void);

void _ZNK7android14SurfaceControl10getSurfaceEv(void) {
  _ZN7android14SurfaceControl10getSurfaceEv();
 }

}
