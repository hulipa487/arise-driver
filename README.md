
# Arise GPU Driver for Phytium

Kernel driver and userspace libraries for the Arise GPU on Phytium ARM64 platforms.

## Contents

- `kernel/` - Kernel module source code (v25.00.51)
- `lib/` - Userspace libraries (DRI, EGL, OpenCL, VDPAU, GBM)
- `config/` - Configuration files for GLVND, OpenCL, and modprobe

## Components

### Kernel Module
- DRM/KMS driver for Arise GPU
- Supports Phytium embedded platforms (aarch64)

### Userspace Libraries
- **OpenGL/EGL**: `libEGL_arise.so`, `libGLX_arise.so`, `arise_vndri.so`
- **OpenCL**: `arise_driocl.so` with compiler support
- **Video**: `arise_drv_video.so`, VDPAU libraries
- **GBM**: Buffer management for Wayland compositors

## License

Proprietary - Copyright (c) Glenfly Tech Co., Ltd.

## Version

25.00.51
