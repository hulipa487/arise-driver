#ifndef cl_clang_storage_class_specifiers
#error Implementation requires cl_clang_storage_class_specifiers extension!
#endif

#pragma OPENCL EXTENSION cl_clang_storage_class_specifiers : enable

#ifdef cl_khr_fp64
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#endif

#ifdef cl_khr_fp16
#pragma OPENCL EXTENSION cl_khr_fp16 : enable
#endif

#ifdef __opencl_c_fp64
#pragma OPENCL EXTENSION __opencl_c_fp64 : enable
#endif

#ifdef __opencl_c_int64
#pragma OPENCL EXTENSION __opencl_c_int64 : enable
#endif

#ifdef __opencl_c_images
#pragma OPENCL EXTENSION __opencl_c_images : enable
#endif

#ifdef __opencl_c_3d_image_writes
#pragma OPENCL EXTENSION __opencl_c_3d_image_writes : enable
#endif

#ifdef __opencl_c_read_write_images
#pragma OPENCL EXTENSION __opencl_c_read_write_images : enable
#endif

#ifdef __opencl_c_pipes
#pragma OPENCL EXTENSION __opencl_c_pipes : enable
#endif

#ifdef __opencl_c_subgroups
#pragma OPENCL EXTENSION __opencl_c_subgroups : enable
#endif

#ifdef __opencl_c_device_enqueue
#pragma OPENCL EXTENSION __opencl_c_device_enqueue : enable
#endif

#ifdef __opencl_c_atomic_scope_device
#pragma OPENCL EXTENSION __opencl_c_atomic_scope_device : enable
#endif

#ifdef __opencl_c_atomic_order_acq_rel
#pragma OPENCL EXTENSION __opencl_c_atomic_order_acq_rel : enable
#endif

#ifdef __opencl_c_atomic_order_seq_cst
#pragma OPENCL EXTENSION __opencl_c_atomic_order_seq_cst : enable
#endif

#ifdef __opencl_c_atomic_scope_all_devices
#pragma OPENCL EXTENSION __opencl_c_atomic_scope_all_devices : enable
#endif

#ifdef __opencl_c_generic_address_space
#pragma OPENCL EXTENSION __opencl_c_generic_address_space : enable
#endif

#ifdef __opencl_c_program_scope_global_variables
#pragma OPENCL EXTENSION __opencl_c_program_scope_global_variables : enable
#endif

#ifdef __opencl_c_work_group_collective_functions
#pragma OPENCL EXTENSION __opencl_c_work_group_collective_functions : enable
#endif

#ifdef __opencl_c_integer_dot_product_input_4x8bit
#pragma OPENCL EXTENSION __opencl_c_integer_dot_product_input_4x8bit : enable
#endif

#ifdef __opencl_c_integer_dot_product_input_4x8bit_packed
#pragma OPENCL EXTENSION __opencl_c_integer_dot_product_input_4x8bit_packed : enable
#endif

//#pragma OPENCL EXTENSION cl_khr_int64_base_atomics : enable
//#pragma OPENCL EXTENSION cl_khr_int64_extended_atomics : enable

/* Function Attributes */
#define _CLC_OVERLOAD __attribute__((overloadable))
#define _CLC_DECL
#define _CLC_DEF __attribute__((always_inline))
#define _CLC_INLINE __attribute__((always_inline)) static inline

/* 5.3.1.1 Image Format Descriptor */
/* cl_channel_order */
#define CLK_R                                        0x10B0
#define CLK_A                                        0x10B1
#define CLK_RG                                       0x10B2
#define CLK_RA                                       0x10B3
#define CLK_RGB                                      0x10B4
#define CLK_RGBA                                     0x10B5
#define CLK_BGRA                                     0x10B6
#define CLK_ARGB                                     0x10B7
#define CLK_INTENSITY                                0x10B8
#define CLK_LUMINANCE                                0x10B9
#define CLK_Rx                                       0x10BA
#define CLK_RGx                                      0x10BB
#define CLK_RGBx                                     0x10BC
#define CLK_DEPTH                                    0x10BD
#define CLK_sRGB                                     0x10BF
#define CLK_sRGBx                                    0x10C0
#define CLK_sRGBA                                    0x10C1
#define CLK_sBGRA                                    0x10C2

/* cl_channel_type */
#define CLK_SNORM_INT8                               0x10D0
#define CLK_SNORM_INT16                              0x10D1
#define CLK_UNORM_INT8                               0x10D2
#define CLK_UNORM_INT16                              0x10D3
#define CLK_UNORM_SHORT_565                          0x10D4
#define CLK_UNORM_SHORT_555                          0x10D5
#define CLK_UNORM_INT_101010                         0x10D6
#define CLK_SIGNED_INT8                              0x10D7
#define CLK_SIGNED_INT16                             0x10D8
#define CLK_SIGNED_INT32                             0x10D9
#define CLK_UNSIGNED_INT8                            0x10DA
#define CLK_UNSIGNED_INT16                           0x10DB
#define CLK_UNSIGNED_INT32                           0x10DC
#define CLK_HALF_FLOAT                               0x10DD
#define CLK_FLOAT                                    0x10DE
	
#define CLK_NORMALIZED_COORDS_TRUE 				0x1
#define CLK_NORMALIZED_COORDS_FALSE 			0x2
#define CLK_ADDRESS_REPEAT 						0x4
#define CLK_ADDRESS_CLAMP_TO_EDGE 				0x8
#define CLK_ADDRESS_CLAMP 						0x10
#define CLK_ADDRESS_NONE 						0x20
#define CLK_FILTER_NEAREST 						0x40
#define CLK_FILTER_LINEAR 						0x80
#define CLK_ADDRESS_MIRRORED_REPEAT 			0x100


/* Error Codes */
#define CLK_SUCCESS                                  0
#define CLK_DEVICE_NOT_FOUND                         -1
#define CLK_DEVICE_NOT_AVAILABLE                     -2
#define CLK_COMPILER_NOT_AVAILABLE                   -3
#define CLK_MEM_OBJECT_ALLOCATION_FAILURE            -4
#define CLK_OUT_OF_RESOURCES                         -5
#define CLK_OUT_OF_HOST_MEMORY                       -6
#define CLK_PROFILING_INFO_NOT_AVAILABLE             -7
#define CLK_MEM_COPY_OVERLAP                         -8
#define CLK_IMAGE_FORMAT_MISMATCH                    -9
#define CLK_IMAGE_FORMAT_NOT_SUPPORTED               -10
#define CLK_BUILD_PROGRAM_FAILURE                    -11
#define CLK_MAP_FAILURE                              -12
#define CLK_MISALIGNED_SUB_BUFFER_OFFSET             -13
#define CLK_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST -14
#define CLK_COMPILE_PROGRAM_FAILURE                  -15
#define CLK_LINKER_NOT_AVAILABLE                     -16
#define CLK_LINK_PROGRAM_FAILURE                     -17
#define CLK_DEVICE_PARTITION_FAILED                  -18
#define CLK_KERNEL_ARG_INFO_NOT_AVAILABLE            -19

#define CLK_INVALID_VALUE                            -30
#define CLK_INVALID_DEVICE_TYPE                      -31
#define CLK_INVALID_PLATFORM                         -32
#define CLK_INVALID_DEVICE                           -33
#define CLK_INVALID_CONTEXT                          -34
#define CLK_INVALID_QUEUE_PROPERTIES                 -35
#define CLK_INVALID_COMMAND_QUEUE                    -36
#define CLK_INVALID_HOST_PTR                         -37
#define CLK_INVALID_MEM_OBJECT                       -38
#define CLK_INVALID_IMAGE_FORMAT_DESCRIPTOR          -39
#define CLK_INVALID_IMAGE_SIZE                       -40
#define CLK_INVALID_SAMPLER                          -41
#define CLK_INVALID_BINARY                           -42
#define CLK_INVALID_BUILD_OPTIONS                    -43
#define CLK_INVALID_PROGRAM                          -44
#define CLK_INVALID_PROGRAM_EXECUTABLE               -45
#define CLK_INVALID_KERNEL_NAME                      -46
#define CLK_INVALID_KERNEL_DEFINITION                -47
#define CLK_INVALID_KERNEL                           -48
#define CLK_INVALID_ARG_INDEX                        -49
#define CLK_INVALID_ARG_VALUE                        -50
#define CLK_INVALID_ARG_SIZE                         -51
#define CLK_INVALID_KERNEL_ARGS                      -52
#define CLK_INVALID_WORK_DIMENSION                   -53
#define CLK_INVALID_WORK_GROUP_SIZE                  -54
#define CLK_INVALID_WORK_ITEM_SIZE                   -55
#define CLK_INVALID_GLOBAL_OFFSET                    -56
#define CLK_INVALID_EVENT_WAIT_LIST                  -57
#define CLK_INVALID_EVENT                            -58
#define CLK_INVALID_OPERATION                        -59
#define CLK_INVALID_GL_OBJECT                        -60
#define CLK_INVALID_BUFFER_SIZE                      -61
#define CLK_INVALID_MIP_LEVEL                        -62
#define CLK_INVALID_GLOBAL_WORK_SIZE                 -63
#define CLK_INVALID_PROPERTY                         -64
#define CLK_INVALID_IMAGE_DESCRIPTOR                 -65
#define CLK_INVALID_COMPILER_OPTIONS                 -66
#define CLK_INVALID_LINKER_OPTIONS                   -67
#define CLK_INVALID_DEVICE_PARTITION_COUNT           -68

/* OpenCL Version */
#define CLK_VERSION_1_0                              1
#define CLK_VERSION_1_1                              1
#define CLK_VERSION_1_2                              1

/* CLK_bool */
#define CLK_FALSE                                    0
#define CLK_TRUE                                     1
#define CLK_BLOCKING                                 CLK_TRUE
#define CLK_NON_BLOCKING                             CLK_FALSE

/* CLK_platform_info */
#define CLK_PLATFORM_PROFILE                         0x0900
#define CLK_PLATFORM_VERSION                         0x0901
#define CLK_PLATFORM_NAME                            0x0902
#define CLK_PLATFORM_VENDOR                          0x0903
#define CLK_PLATFORM_EXTENSIONS                      0x0904

/* CLK_device_type - bitfield */
#define CLK_DEVICE_TYPE_DEFAULT                      (1 << 0)
#define CLK_DEVICE_TYPE_CPU                          (1 << 1)
#define CLK_DEVICE_TYPE_GPU                          (1 << 2)
#define CLK_DEVICE_TYPE_ACCELERATOR                  (1 << 3)
#define CLK_DEVICE_TYPE_CUSTOM                       (1 << 4)
#define CLK_DEVICE_TYPE_ALL                          0xFFFFFFFF

/* CLK_device_info */
#define CLK_DEVICE_TYPE                              0x1000
#define CLK_DEVICE_VENDOR_ID                         0x1001
#define CLK_DEVICE_MAX_COMPUTE_UNITS                 0x1002
#define CLK_DEVICE_MAX_WORK_ITEM_DIMENSIONS          0x1003
#define CLK_DEVICE_MAX_WORK_GROUP_SIZE               0x1004
#define CLK_DEVICE_MAX_WORK_ITEM_SIZES               0x1005
#define CLK_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR       0x1006
#define CLK_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT      0x1007
#define CLK_DEVICE_PREFERRED_VECTOR_WIDTH_INT        0x1008
#define CLK_DEVICE_PREFERRED_VECTOR_WIDTH_LONG       0x1009
#define CLK_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT      0x100A
#define CLK_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE     0x100B
#define CLK_DEVICE_MAX_CLOCK_FREQUENCY               0x100C
#define CLK_DEVICE_ADDRESS_BITS                      0x100D
#define CLK_DEVICE_MAX_READ_IMAGE_ARGS               0x100E
#define CLK_DEVICE_MAX_WRITE_IMAGE_ARGS              0x100F
#define CLK_DEVICE_MAX_MEM_ALLOC_SIZE                0x1010
#define CLK_DEVICE_IMAGE2D_MAX_WIDTH                 0x1011
#define CLK_DEVICE_IMAGE2D_MAX_HEIGHT                0x1012
#define CLK_DEVICE_IMAGE3D_MAX_WIDTH                 0x1013
#define CLK_DEVICE_IMAGE3D_MAX_HEIGHT                0x1014
#define CLK_DEVICE_IMAGE3D_MAX_DEPTH                 0x1015
#define CLK_DEVICE_IMAGE_SUPPORT                     0x1016
#define CLK_DEVICE_MAX_PARAMETER_SIZE                0x1017
#define CLK_DEVICE_MAX_SAMPLERS                      0x1018
#define CLK_DEVICE_MEM_BASE_ADDR_ALIGN               0x1019
#define CLK_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE          0x101A
#define CLK_DEVICE_SINGLE_FP_CONFIG                  0x101B
#define CLK_DEVICE_GLOBAL_MEM_CACHE_TYPE             0x101C
#define CLK_DEVICE_GLOBAL_MEM_CACHELINE_SIZE         0x101D
#define CLK_DEVICE_GLOBAL_MEM_CACHE_SIZE             0x101E
#define CLK_DEVICE_GLOBAL_MEM_SIZE                   0x101F
#define CLK_DEVICE_MAX_CONSTANT_BUFFER_SIZE          0x1020
#define CLK_DEVICE_MAX_CONSTANT_ARGS                 0x1021
#define CLK_DEVICE_LOCAL_MEM_TYPE                    0x1022
#define CLK_DEVICE_LOCAL_MEM_SIZE                    0x1023
#define CLK_DEVICE_ERROR_CORRECTION_SUPPORT          0x1024
#define CLK_DEVICE_PROFILING_TIMER_RESOLUTION        0x1025
#define CLK_DEVICE_ENDIAN_LITTLE                     0x1026
#define CLK_DEVICE_AVAILABLE                         0x1027
#define CLK_DEVICE_COMPILER_AVAILABLE                0x1028
#define CLK_DEVICE_EXECUTION_CAPABILITIES            0x1029
#define CLK_DEVICE_QUEUE_PROPERTIES                  0x102A
#define CLK_DEVICE_NAME                              0x102B
#define CLK_DEVICE_VENDOR                            0x102C
#define CLK_DRIVER_VERSION                           0x102D
#define CLK_DEVICE_PROFILE                           0x102E
#define CLK_DEVICE_VERSION                           0x102F
#define CLK_DEVICE_EXTENSIONS                        0x1030
#define CLK_DEVICE_PLATFORM                          0x1031
#define CLK_DEVICE_DOUBLE_FP_CONFIG                  0x1032
/* 0x1033 reserved for CLK_DEVICE_HALF_FP_CONFIG */
#define CLK_DEVICE_PREFERRED_VECTOR_WIDTH_HALF       0x1034
#define CLK_DEVICE_HOST_UNIFIED_MEMORY               0x1035
#define CLK_DEVICE_NATIVE_VECTOR_WIDTH_CHAR          0x1036
#define CLK_DEVICE_NATIVE_VECTOR_WIDTH_SHORT         0x1037
#define CLK_DEVICE_NATIVE_VECTOR_WIDTH_INT           0x1038
#define CLK_DEVICE_NATIVE_VECTOR_WIDTH_LONG          0x1039
#define CLK_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT         0x103A
#define CLK_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE        0x103B
#define CLK_DEVICE_NATIVE_VECTOR_WIDTH_HALF          0x103C
#define CLK_DEVICE_OPENCL_C_VERSION                  0x103D
#define CLK_DEVICE_LINKER_AVAILABLE                  0x103E
#define CLK_DEVICE_BUILT_IN_KERNELS                  0x103F
#define CLK_DEVICE_IMAGE_MAX_BUFFER_SIZE             0x1040
#define CLK_DEVICE_IMAGE_MAX_ARRAY_SIZE              0x1041
#define CLK_DEVICE_PARENT_DEVICE                     0x1042
#define CLK_DEVICE_PARTITION_MAX_SUB_DEVICES         0x1043
#define CLK_DEVICE_PARTITION_PROPERTIES              0x1044
#define CLK_DEVICE_PARTITION_AFFINITY_DOMAIN         0x1045
#define CLK_DEVICE_PARTITION_TYPE                    0x1046
#define CLK_DEVICE_REFERENCE_COUNT                   0x1047
#define CLK_DEVICE_PREFERRED_INTEROP_USER_SYNC       0x1048
#define CLK_DEVICE_PRINTF_BUFFER_SIZE                0x1049
#define CLK_DEVICE_IMAGE_PITCH_ALIGNMENT             0x104A
#define CLK_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT      0x104B

/* CLK_device_fp_config - bitfield */
#define CLK_FP_DENORM                                (1 << 0)
#define CLK_FP_INF_NAN                               (1 << 1)
#define CLK_FP_ROUND_TO_NEAREST                      (1 << 2)
#define CLK_FP_ROUND_TO_ZERO                         (1 << 3)
#define CLK_FP_ROUND_TO_INF                          (1 << 4)
#define CLK_FP_FMA                                   (1 << 5)
#define CLK_FP_SOFT_FLOAT                            (1 << 6)
#define CLK_FP_CORRECTLY_ROUNDED_DIVIDE_SQRT         (1 << 7)

/* CLK_device_mem_cache_type */
#define CLK_NONE                                     0x0
#define CLK_READ_ONLY_CACHE                          0x1
#define CLK_READ_WRITE_CACHE                         0x2

/* CLK_device_local_mem_type */
#define CLK_LOCAL                                    0x1
#define CLK_GLOBAL                                   0x2

/* CLK_device_exec_capabilities - bitfield */
#define CLK_EXEC_KERNEL                              (1 << 0)
#define CLK_EXEC_NATIVE_KERNEL                       (1 << 1)

/* CLK_command_queue_properties - bitfield */
#define CLK_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE      (1 << 0)
#define CLK_QUEUE_PROFILING_ENABLE                   (1 << 1)

/* CLK_context_info  */
#define CLK_CONTEXT_REFERENCE_COUNT                  0x1080
#define CLK_CONTEXT_DEVICES                          0x1081
#define CLK_CONTEXT_PROPERTIES                       0x1082
#define CLK_CONTEXT_NUM_DEVICES                      0x1083

/* CLK_context_properties */
#define CLK_CONTEXT_PLATFORM                         0x1084
#define CLK_CONTEXT_INTEROP_USER_SYNC                0x1085
    
/* CLK_device_partition_property */
#define CLK_DEVICE_PARTITION_EQUALLY                 0x1086
#define CLK_DEVICE_PARTITION_BY_COUNTS               0x1087
#define CLK_DEVICE_PARTITION_BY_COUNTS_LIST_END      0x0
#define CLK_DEVICE_PARTITION_BY_AFFINITY_DOMAIN      0x1088
    
/* CLK_device_affinity_domain */
#define CLK_DEVICE_AFFINITY_DOMAIN_NUMA                     (1 << 0)
#define CLK_DEVICE_AFFINITY_DOMAIN_L4_CACHE                 (1 << 1)
#define CLK_DEVICE_AFFINITY_DOMAIN_L3_CACHE                 (1 << 2)
#define CLK_DEVICE_AFFINITY_DOMAIN_L2_CACHE                 (1 << 3)
#define CLK_DEVICE_AFFINITY_DOMAIN_L1_CACHE                 (1 << 4)
#define CLK_DEVICE_AFFINITY_DOMAIN_NEXT_PARTITIONABLE       (1 << 5)

/* CLK_command_queue_info */
#define CLK_QUEUE_CONTEXT                            0x1090
#define CLK_QUEUE_DEVICE                             0x1091
#define CLK_QUEUE_REFERENCE_COUNT                    0x1092
#define CLK_QUEUE_PROPERTIES                         0x1093

/* CLK_mem_flags - bitfield */
#define CLK_MEM_READ_WRITE                           (1 << 0)
#define CLK_MEM_WRITE_ONLY                           (1 << 1)
#define CLK_MEM_READ_ONLY                            (1 << 2)
#define CLK_MEM_USE_HOST_PTR                         (1 << 3)
#define CLK_MEM_ALLOC_HOST_PTR                       (1 << 4)
#define CLK_MEM_COPY_HOST_PTR                        (1 << 5)
// reserved                                         (1 << 6)    
#define CLK_MEM_HOST_WRITE_ONLY                      (1 << 7)
#define CLK_MEM_HOST_READ_ONLY                       (1 << 8)
#define CLK_MEM_HOST_NO_ACCESS                       (1 << 9)

/* CLK_mem_migration_flags - bitfield */
#define CLK_MIGRATE_MEM_OBJECT_HOST                  (1 << 0)
#define CLK_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED     (1 << 1)


/* CLK_mem_object_type */
#define CLK_MEM_OBJECT_BUFFER                        0x10F0
#define CLK_MEM_OBJECT_IMAGE2D                       0x10F1
#define CLK_MEM_OBJECT_IMAGE3D                       0x10F2
#define CLK_MEM_OBJECT_IMAGE2D_ARRAY                 0x10F3
#define CLK_MEM_OBJECT_IMAGE1D                       0x10F4
#define CLK_MEM_OBJECT_IMAGE1D_ARRAY                 0x10F5
#define CLK_MEM_OBJECT_IMAGE1D_BUFFER                0x10F6

/* CLK_mem_info */
#define CLK_MEM_TYPE                                 0x1100
#define CLK_MEM_FLAGS                                0x1101
#define CLK_MEM_SIZE                                 0x1102
#define CLK_MEM_HOST_PTR                             0x1103
#define CLK_MEM_MAP_COUNT                            0x1104
#define CLK_MEM_REFERENCE_COUNT                      0x1105
#define CLK_MEM_CONTEXT                              0x1106
#define CLK_MEM_ASSOCIATED_MEMOBJECT                 0x1107
#define CLK_MEM_OFFSET                               0x1108

/* CLK_image_info */
#define CLK_IMAGE_FORMAT                             0x1110
#define CLK_IMAGE_ELEMENT_SIZE                       0x1111
#define CLK_IMAGE_ROW_PITCH                          0x1112
#define CLK_IMAGE_SLICE_PITCH                        0x1113
#define CLK_IMAGE_WIDTH                              0x1114
#define CLK_IMAGE_HEIGHT                             0x1115
#define CLK_IMAGE_DEPTH                              0x1116
#define CLK_IMAGE_ARRAY_SIZE                         0x1117
#define CLK_IMAGE_BUFFER                             0x1118
#define CLK_IMAGE_NUM_MIP_LEVELS                     0x1119
#define CLK_IMAGE_NUM_SAMPLES                        0x111A

/* CLK_sampler_info */
#define CLK_SAMPLER_REFERENCE_COUNT                  0x1150
#define CLK_SAMPLER_CONTEXT                          0x1151
#define CLK_SAMPLER_NORMALIZED_COORDS                0x1152
#define CLK_SAMPLER_ADDRESSING_MODE                  0x1153
#define CLK_SAMPLER_FILTER_MODE                      0x1154

/* CLK_map_flags - bitfield */
#define CLK_MAP_READ                                 (1 << 0)
#define CLK_MAP_WRITE                                (1 << 1)
#define CLK_MAP_WRITE_INVALIDATE_REGION              (1 << 2)

/* CLK_program_info */
#define CLK_PROGRAM_REFERENCE_COUNT                  0x1160
#define CLK_PROGRAM_CONTEXT                          0x1161
#define CLK_PROGRAM_NUM_DEVICES                      0x1162
#define CLK_PROGRAM_DEVICES                          0x1163
#define CLK_PROGRAM_SOURCE                           0x1164
#define CLK_PROGRAM_BINARY_SIZES                     0x1165
#define CLK_PROGRAM_BINARIES                         0x1166
#define CLK_PROGRAM_NUM_KERNELS                      0x1167
#define CLK_PROGRAM_KERNEL_NAMES                     0x1168

/* CLK_program_build_info */
#define CLK_PROGRAM_BUILD_STATUS                     0x1181
#define CLK_PROGRAM_BUILD_OPTIONS                    0x1182
#define CLK_PROGRAM_BUILD_LOG                        0x1183
#define CLK_PROGRAM_BINARY_TYPE                      0x1184
    
/* CLK_program_binary_type */
#define CLK_PROGRAM_BINARY_TYPE_NONE                 0x0
#define CLK_PROGRAM_BINARY_TYPE_COMPILED_OBJECT      0x1
#define CLK_PROGRAM_BINARY_TYPE_LIBRARY              0x2
#define CLK_PROGRAM_BINARY_TYPE_EXECUTABLE           0x4

/* CLK_build_status */
#define CLK_BUILD_SUCCESS                            0
#define CLK_BUILD_NONE                               -1
#define CLK_BUILD_ERROR                              -2
#define CLK_BUILD_IN_PROGRESS                        -3

/* CLK_kernel_info */
#define CLK_KERNEL_FUNCTION_NAME                     0x1190
#define CLK_KERNEL_NUM_ARGS                          0x1191
#define CLK_KERNEL_REFERENCE_COUNT                   0x1192
#define CLK_KERNEL_CONTEXT                           0x1193
#define CLK_KERNEL_PROGRAM                           0x1194
#define CLK_KERNEL_ATTRIBUTES                        0x1195

/* CLK_kernel_arg_info */
#define CLK_KERNEL_ARG_ADDRESS_QUALIFIER             0x1196
#define CLK_KERNEL_ARG_ACCESS_QUALIFIER              0x1197
#define CLK_KERNEL_ARG_TYPE_NAME                     0x1198
#define CLK_KERNEL_ARG_TYPE_QUALIFIER                0x1199
#define CLK_KERNEL_ARG_NAME                          0x119A

/* CLK_kernel_arg_address_qualifier */
#define CLK_KERNEL_ARG_ADDRESS_GLOBAL                0x119B
#define CLK_KERNEL_ARG_ADDRESS_LOCAL                 0x119C
#define CLK_KERNEL_ARG_ADDRESS_CONSTANT              0x119D
#define CLK_KERNEL_ARG_ADDRESS_PRIVATE               0x119E

/* CLK_kernel_arg_access_qualifier */
#define CLK_KERNEL_ARG_ACCESS_READ_ONLY              0x11A0
#define CLK_KERNEL_ARG_ACCESS_WRITE_ONLY             0x11A1
#define CLK_KERNEL_ARG_ACCESS_READ_WRITE             0x11A2
#define CLK_KERNEL_ARG_ACCESS_NONE                   0x11A3
    
/* CLK_kernel_arg_type_qualifer */
#define CLK_KERNEL_ARG_TYPE_NONE                     0
#define CLK_KERNEL_ARG_TYPE_CONST                    (1 << 0)
#define CLK_KERNEL_ARG_TYPE_RESTRICT                 (1 << 1)
#define CLK_KERNEL_ARG_TYPE_VOLATILE                 (1 << 2)

/* CLK_kernel_work_group_info */
#define CLK_KERNEL_WORK_GROUP_SIZE                   0x11B0
#define CLK_KERNEL_COMPILE_WORK_GROUP_SIZE           0x11B1
#define CLK_KERNEL_LOCAL_MEM_SIZE                    0x11B2
#define CLK_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE 0x11B3
#define CLK_KERNEL_PRIVATE_MEM_SIZE                  0x11B4
#define CLK_KERNEL_GLOBAL_WORK_SIZE                  0x11B5

/* CLK_event_info  */
#define CLK_EVENT_COMMAND_QUEUE                      0x11D0
#define CLK_EVENT_COMMAND_TYPE                       0x11D1
#define CLK_EVENT_REFERENCE_COUNT                    0x11D2
#define CLK_EVENT_COMMAND_EXECUTION_STATUS           0x11D3
#define CLK_EVENT_CONTEXT                            0x11D4

/* CLK_command_type */
#define CLK_COMMAND_NDRANGE_KERNEL                   0x11F0
#define CLK_COMMAND_TASK                             0x11F1
#define CLK_COMMAND_NATIVE_KERNEL                    0x11F2
#define CLK_COMMAND_READ_BUFFER                      0x11F3
#define CLK_COMMAND_WRITE_BUFFER                     0x11F4
#define CLK_COMMAND_COPY_BUFFER                      0x11F5
#define CLK_COMMAND_READ_IMAGE                       0x11F6
#define CLK_COMMAND_WRITE_IMAGE                      0x11F7
#define CLK_COMMAND_COPY_IMAGE                       0x11F8
#define CLK_COMMAND_COPY_IMAGE_TO_BUFFER             0x11F9
#define CLK_COMMAND_COPY_BUFFER_TO_IMAGE             0x11FA
#define CLK_COMMAND_MAP_BUFFER                       0x11FB
#define CLK_COMMAND_MAP_IMAGE                        0x11FC
#define CLK_COMMAND_UNMAP_MEM_OBJECT                 0x11FD
#define CLK_COMMAND_MARKER                           0x11FE
#define CLK_COMMAND_ACQUIRE_GL_OBJECTS               0x11FF
#define CLK_COMMAND_RELEASE_GL_OBJECTS               0x1200
#define CLK_COMMAND_READ_BUFFER_RECT                 0x1201
#define CLK_COMMAND_WRITE_BUFFER_RECT                0x1202
#define CLK_COMMAND_COPY_BUFFER_RECT                 0x1203
#define CLK_COMMAND_USER                             0x1204
#define CLK_COMMAND_BARRIER                          0x1205
#define CLK_COMMAND_MIGRATE_MEM_OBJECTS              0x1206
#define CLK_COMMAND_FILL_BUFFER                      0x1207
#define CLK_COMMAND_FILL_IMAGE                       0x1208

/* command execution status */
#define CLK_COMPLETE                                 0x0
#define CLK_RUNNING                                  0x1
#define CLK_SUBMITTED                                0x2
#define CLK_QUEUED                                   0x3

/* CLK_buffer_create_type  */
#define CLK_BUFFER_CREATE_TYPE_REGION                0x1220

/* CLK_profiling_info  */
#define CLK_PROFILING_COMMAND_QUEUED                 0x1280
#define CLK_PROFILING_COMMAND_SUBMIT                 0x1281
#define CLK_PROFILING_COMMAND_START                  0x1282
#define CLK_PROFILING_COMMAND_END                    0x1283

#define CLK_ENQUEUE_FLAGS_NO_WAIT                    0x0
#define CLK_ENQUEUE_FLAGS_WAIT_KERNEL                0x1
#define CLK_ENQUEUE_FLAGS_WAIT_WORK_GROUP            0x2

/* 6.1 Supported Data Types */
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef __SIZE_TYPE__ size_t;
typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __INTPTR_TYPE__ intptr_t;
typedef __UINTPTR_TYPE__ uintptr_t;

#ifdef __cplusplus
#  if !defined(__MINGW32__) && !defined(_MSC_VER)
#    define NULL __null
#  else
#    define NULL 0
#  endif
#else
#  define NULL ((void*)0)
#endif

/* 6.1.2 Built-in Vector Data Types */
typedef __attribute__((ext_vector_type(2))) char char2;
typedef __attribute__((ext_vector_type(3))) char char3;
typedef __attribute__((ext_vector_type(4))) char char4;
typedef __attribute__((ext_vector_type(8))) char char8;
typedef __attribute__((ext_vector_type(16))) char char16;

typedef __attribute__((ext_vector_type(2))) uchar uchar2;
typedef __attribute__((ext_vector_type(3))) uchar uchar3;
typedef __attribute__((ext_vector_type(4))) uchar uchar4;
typedef __attribute__((ext_vector_type(8))) uchar uchar8;
typedef __attribute__((ext_vector_type(16))) uchar uchar16;

typedef __attribute__((ext_vector_type(2))) short short2;
typedef __attribute__((ext_vector_type(3))) short short3;
typedef __attribute__((ext_vector_type(4))) short short4;
typedef __attribute__((ext_vector_type(8))) short short8;
typedef __attribute__((ext_vector_type(16))) short short16;

typedef __attribute__((ext_vector_type(2))) ushort ushort2;
typedef __attribute__((ext_vector_type(3))) ushort ushort3;
typedef __attribute__((ext_vector_type(4))) ushort ushort4;
typedef __attribute__((ext_vector_type(8))) ushort ushort8;
typedef __attribute__((ext_vector_type(16))) ushort ushort16;

typedef __attribute__((ext_vector_type(2))) int int2;
typedef __attribute__((ext_vector_type(3))) int int3;
typedef __attribute__((ext_vector_type(4))) int int4;
typedef __attribute__((ext_vector_type(8))) int int8;
typedef __attribute__((ext_vector_type(16))) int int16;

typedef __attribute__((ext_vector_type(2))) uint uint2;
typedef __attribute__((ext_vector_type(3))) uint uint3;
typedef __attribute__((ext_vector_type(4))) uint uint4;
typedef __attribute__((ext_vector_type(8))) uint uint8;
typedef __attribute__((ext_vector_type(16))) uint uint16;

typedef __attribute__((ext_vector_type(2))) long long2;
typedef __attribute__((ext_vector_type(3))) long long3;
typedef __attribute__((ext_vector_type(4))) long long4;
typedef __attribute__((ext_vector_type(8))) long long8;
typedef __attribute__((ext_vector_type(16))) long long16;

typedef __attribute__((ext_vector_type(2))) ulong ulong2;
typedef __attribute__((ext_vector_type(3))) ulong ulong3;
typedef __attribute__((ext_vector_type(4))) ulong ulong4;
typedef __attribute__((ext_vector_type(8))) ulong ulong8;
typedef __attribute__((ext_vector_type(16))) ulong ulong16;

typedef __attribute__((ext_vector_type(2))) float float2;
typedef __attribute__((ext_vector_type(3))) float float3;
typedef __attribute__((ext_vector_type(4))) float float4;
typedef __attribute__((ext_vector_type(8))) float float8;
typedef __attribute__((ext_vector_type(16))) float float16;

/* 6.1.1.1 The half data type */
#ifdef cl_khr_fp16
typedef __attribute__((ext_vector_type(2))) half half2;
typedef __attribute__((ext_vector_type(3))) half half3;
typedef __attribute__((ext_vector_type(4))) half half4;
typedef __attribute__((ext_vector_type(8))) half half8;
typedef __attribute__((ext_vector_type(16))) half half16;
#endif

/* 9.3 Double Precision Floating-Point */
#ifdef cl_khr_fp64
typedef __attribute__((ext_vector_type(2))) double double2;
typedef __attribute__((ext_vector_type(3))) double double3;
typedef __attribute__((ext_vector_type(4))) double double4;
typedef __attribute__((ext_vector_type(8))) double double8;
typedef __attribute__((ext_vector_type(16))) double double16;
#endif

typedef int clk_profiling_info;

typedef uchar	uchar_32_32;
typedef ushort  ushort_32_32;
typedef uint	uint_32_32;
typedef float	float_32_32;
typedef uint4	uint_4_32;
typedef float4	float_4_32;
typedef uchar4	uchar_4_32;
typedef ushort4	ushort_4_32;
typedef uint4   uchar_8_32;
typedef uint4   ushort_8_32;
typedef char	char_32_32;
typedef short  	short_32_32;
typedef int		int_32_32;
typedef int4	int_4_32;
typedef char4	char_4_32;
typedef short4	short_4_32;
typedef int4   	char_8_32;
typedef int4   	short_8_32;

typedef float4	fragment__matrix_16_16_16_float;

/* contant values used by built-in funcs*/
#ifndef RCP_PI_VALUE_F
#define RCP_PI_VALUE_F 0.31830988618379067153776752674503f
#endif

#ifndef RCP_PI_VALUE
#define RCP_PI_VALUE 0.31830988618379067153776752674503
#endif

#ifndef M_PI
#define M_PI 3.141592653589793115998
#endif

#ifndef M_PI_2
#define M_PI_2 1.570796326794896557999
#endif

#ifndef M_PI_4
#define M_PI_4 0.785398163397448278999
#endif

#ifndef RCP_PI_2_1_F
#define RCP_PI_2_1_F 0.636474609375f	// 12 bit accuracy(1-12)
#endif

#ifndef RCP_PI_2_2_F
#define RCP_PI_2_2_F 0.000145137310028f	// 12 bit accuracy(13-24)
#endif

#ifndef RCP_PI_2_3_F
#define RCP_PI_2_3_F 0.0000000256768544205f	// 12 bit accuracy(25-36)
#endif

#ifndef RCP_PI_2_4_F
#define RCP_PI_2_4_F 0.0000000000056989225755350534900574481369491f	// 24 bit accuracy(37-60)
#endif

#ifndef RCP_PI_2_1
#define RCP_PI_2_1 0.636474609375	// 12 bit accuracy(1-12)
#endif

#ifndef RCP_PI_2_2
#define RCP_PI_2_2 0.000145137310028	// 12 bit accuracy(13-24)
#endif

#ifndef RCP_PI_2_3
#define RCP_PI_2_3 0.0000000256768544205	// 12 bit accuracy(25-36)
#endif

#ifndef RCP_PI_2_4
#define RCP_PI_2_4 0.0000000000056989225755350534900574481369491	// 24 bit accuracy(37-60)
#endif

#ifndef CSTONE
#define CSTONE 1.0f
#endif 

/* used for calculating sin(x) */
#define M_ASIN_C3_F	0.1666666666666666666666666666667f   // 1/(2*3)
#define M_ASIN_C5_F	0.075f                                                  // (1*3)/(2*4*5)
#define M_ASIN_C7_F	0.0446428571428571428571428571429f   // (1*3*5)/(2*4*6*7)
#define M_ASIN_C9_F	0.0303819444444444444444444444444f   // (1*3*5*7)/(2*4*6*8*9)
#define M_ASIN_C11_F	0.0223721590909090909090909090909f   // (1*3*5*7*9)/(2*4*6*8*10*11)
#define M_ASIN_C13_F	0.0173527644230769230769230769231f  // (1*3*5*7*9*11)/(2*4*6*8*10*12*13)
#define M_ASIN_C15_F	0.01396484375f  // (1*3*5*7*9*11*13)/(2*4*6*8*10*12*14*15)
#define M_ASIN_C17_F	0.0115518008961397058823529411765f  // (1*3*5*7*9*11*13*15)/(2*4*6*8*10*12*14*16*17)
/* used for calc atan */
#define M_ATAN_C3_F	0.3333333333333333333333333333333f	//1/3
#define M_ATAN_C5_F	0.2f																//1/5
#define M_ATAN_C7_F	0.1428571428571428571428571428571f	//1/7
#define M_ATAN_C9_F	0.1111111111111111111111111111111f	//1/9
#define M_ATAN_C11_F 0.0909090909090909090909090909091f	//1/11
#define M_ATAN_C13_F 0.0769230769230769230769230769230f	//1/13

#define M_SIN_C3_F	0.1666666666666666666666666666667f  // 1/3!
#define M_SIN_C5_F	0.0083333333333333333333333333333f  // 1/5!
#define M_SIN_C7_F	0.0001984126984126984126984126984f  // 1/7!
#define M_SIN_C9_F	0.0000027557319223985890652557319f  // 1/9!
#define M_SIN_C11_F	0.0000000250521083854417187750521f  // 1/11!
#define M_SIN_C13_F	0.0000000001605904383682161459939f  // 1/13!

#define M_COS_C2_F	0.5f   															// 1/2!
#define M_COS_C4_F	0.04166666666666666666666666666667f // 1/4!
#define M_COS_C6_F	0.00138888888888888888888888888889f // 1/6!
#define M_COS_C8_F	0.00002480158730158730158730158731f // 1/8!
#define M_COS_C10_F	0.00000027557319223985890652557319f // 1/10!
#define M_COS_C12_F	0.00000000208767569878680989792101f // 1/12!
//#define M_COS_C14	0.00000000001147074559772972471385f   // 1/14!

#define M_LOG_E_2_F	1.4423828125f   											// high 12bit log2(e)
#define LOW_LOG_E_2_F	0.000312228396069f									// low 24bit log2(e)
#define M_LOG_10_2_F	3.3212890625f   											// high 12bit log2(10)
#define LOW_LOG_10_2_F	0.00063903238736234787f							// low 24bit log2(10)

/* used for calc erf*/
/* erf(x) = (2/sqrt(pi)) * (x + (-1/3)*(x^3) + (1/10)*(x^5) + (-1/42)*(x^7))
erfc(x) = 1 - erf(x) = 1 + ((2/sqrt(pi)) * (-x + (1/3)*(x^3) + (-1/10)*(x^5) + (1/42)*(x^7)))
*/
#define M_ERF_C1_F       1.1283791670955235024662212286646f
#define M_ERF_C3_F       0.3761263890318411674887404095547f
#define M_ERF_C5_F       0.1128379167095523502466221228664f
#define M_ERF_C7_F       0.0268661706451315119634814578253f

// for double calc
#define M_ASIN_C3	0.1666666666666666666666666666667   // 1/(2*3)
#define M_ASIN_C5	0.075                                // (1*3)/(2*4*5)
#define M_ASIN_C7	0.0446428571428571428571428571429   // (1*3*5)/(2*4*6*7)
#define M_ASIN_C9	0.0303819444444444444444444444444   // (1*3*5*7)/(2*4*6*8*9)
#define M_ASIN_C11	0.0223721590909090909090909090909   // (1*3*5*7*9)/(2*4*6*8*10*11)
#define M_ASIN_C13	0.0173527644230769230769230769231  // (1*3*5*7*9*11)/(2*4*6*8*10*12*13)
#define M_ASIN_C15	0.01396484375  // (1*3*5*7*9*11*13)/(2*4*6*8*10*12*14*15)
#define M_ASIN_C17	0.0115518008961397058823529411765  // (1*3*5*7*9*11*13*15)/(2*4*6*8*10*12*14*16*17)
/* used for calc atan */
#define M_ATAN_C3	0.3333333333333333333333333333333   //1/3
#define M_ATAN_C5	0.2															    //1/5
#define M_ATAN_C7	0.1428571428571428571428571428571   //1/7
#define M_ATAN_C9	0.1111111111111111111111111111111   //1/9
#define M_ATAN_C11 0.0909090909090909090909090909091  //1/11
#define M_ATAN_C13 0.0769230769230769230769230769230  //1/13
#define M_ATAN_C15 0.0666666666666666666666666666667  //1/15
#define M_ATAN_C17 0.0588235294117647058823529411764  //1/17
#define M_ATAN_C19 0.0526315789473684210526315789473  //1/19
#define M_ATAN_C21 0.0476190476190476190476190476190  //1/21
#define M_ATAN_C23 0.0434782608695652173913043478260  //1/23
#define M_ATAN_C25 0.04                               //1/25
#define M_ATAN_C27 0.0370370370370370370370370370370  //1/27
#define M_ATAN_C29 0.0344827586206896551724137931034  //1/29
#define M_ATAN_C31 0.0322580645161290322580645161290  //1/31

#define M_SIN_C3	0.1666666666666666666666666666667  // 1/3!
#define M_SIN_C5	0.0083333333333333333333333333333  // 1/5!
#define M_SIN_C7	0.0001984126984126984126984126984  // 1/7!
#define M_SIN_C9	0.0000027557319223985890652557319  // 1/9!
#define M_SIN_C11	0.0000000250521083854417187750521  // 1/11!
#define M_SIN_C13	0.0000000001605904383682161459939  // 1/13!

#define M_COS_C2	0.5   														 // 1/2!
#define M_COS_C4	0.04166666666666666666666666666667 // 1/4!
#define M_COS_C6	0.00138888888888888888888888888889 // 1/6!
#define M_COS_C8	0.00002480158730158730158730158731 // 1/8!
#define M_COS_C10	0.00000027557319223985890652557319 // 1/10!
#define M_COS_C12	0.00000000208767569878680989792101 // 1/12!
#define M_COS_C14	0.00000000001147074559772972471385 // 1/14!

#define M_LOG_E_2	1.4423828125   											// high 12bit log2(e)
#define LOW_LOG_E_2	0.000312228396069									// low 24bit log2(e)
#define M_LOG_10_2	3.3212890625   											// high 12bit log2(10)
#define LOW_LOG_10_2	0.00063903238736234787							// low 24bit log2(10)

/* used for calc erf*/
/* erf(x) = (2/sqrt(pi)) * (x + (-1/3)*(x^3) + (1/10)*(x^5) + (-1/42)*(x^7))
   erfc(x) = 1 - erf(x) = 1 + ((2/sqrt(pi)) * (-x + (1/3)*(x^3) + (-1/10)*(x^5) + (1/42)*(x^7)))
*/
#define M_ERF_C1       1.1283791670955235024662212286646
#define M_ERF_C3       0.3761263890318411674887404095547
#define M_ERF_C5       0.1128379167095523502466221228664
#define M_ERF_C7       0.0268661706451315119634814578253


/* These definitions, used by float functions,
   are for both 32 and 64 bit machines */
#define SIGNBIT_SP32      0x80000000U
#define EXSIGNBIT_SP32    0x7fffffffU
#define EXPBITS_SP32      0x7f800000U
#define MANTBITS_SP32     0x007fffffU
#define ONEEXPBITS_SP32   0x3f800000U
#define TWOEXPBITS_SP32   0x40000000U
#define HALFEXPBITS_SP32  0x3f000000U
#define IMPBIT_SP32       0x00800000U
#define QNANBITPATT_SP32  0x7fc00000U
#define INDEFBITPATT_SP32 0xffc00000U
#define PINFBITPATT_SP32  0x7f800000U
#define NINFBITPATT_SP32  0xff800000U
#define EXPBIAS_SP32      127
#define EXPSHIFTBITS_SP32 23
#define BIASEDEMIN_SP32   1
#define EMIN_SP32         -126
#define BIASEDEMAX_SP32   254
#define EMAX_SP32         127
#define LAMBDA_SP32       1.0e30
#define MANTLENGTH_SP32   24
#define BASEDIGITS_SP32   7

#define SIGNBIT_DP64      0x8000000000000000ULL
#define EXPBITS_DP64      0x7ff0000000000000ULL
#define MANTBITS_DP64     0x000fffffffffffffULL
#define ONEEXPBITS_DP64   0x3ff0000000000000ULL
#define TWOEXPBITS_DP64   0x4000000000000000ULL
#define HALFEXPBITS_DP64  0x3fe0000000000000ULL
#define IMPBIT_DP64       0x0010000000000000ULL
#define QNANBITPATT_DP64  0x7ff8000000000000ULL
#define INDEFBITPATT_DP64 0xfff8000000000000ULL
#define PINFBITPATT_DP64  0x7ff0000000000000ULL
#define NINFBITPATT_DP64  0xfff0000000000000ULL
#define EXPBIAS_DP64      1023
#define EXPSHIFTBITS_DP64 52
#define BIASEDEMIN_DP64   1
#define EMIN_DP64         -1022
#define BIASEDEMAX_DP64   2046
#define EMAX_DP64         1023
#define LAMBDA_DP64       1.0e300
#define MANTLENGTH_DP64   53
#define BASEDIGITS_DP64   15

#define EXPBITS_HIGHPART_DP64   0x7ff00000U
#define MANTBITS_HIGHPART_DP64  0x000fffffU
#define MANTBITS_LOWPART_DP64   0xffffffffU

#define SIGNBIT_HP16      0x8000U
#define EXPBITS_HP16      0x7c00U
#define MANTBITS_HP16     0x03ffU

// most significant bit mask
#define _SCHAR_MSB_BIT         0x40
#define _UCHAR_MSB_BIT         0x80
#define _SHRT_MSB_BIT          0x4000
#define _USHRT_MSB_BIT         0x8000
#define _INT_MSB_BIT           0x40000000
#define _UINT_MSB_BIT          0x80000000
#define _LONG_MSB_BIT          0x4000000000000000LL
#define _ULONG_MSB_BIT         0x8000000000000000ULL

#ifndef LLONG_MAX
#define LLONG_MAX     				9223372036854775807ULL        /* maximum signed long long int value */
#define LLONG_MIN   					(-9223372036854775807LL - 1)  /* minimum signed long long int value */
#define ULLONG_MAX    				0xffffffffffffffffULL         /* maximum unsigned long long int value */
#endif

#define _LONG_MAX             LLONG_MAX
#define _LONG_MIN             LLONG_MIN
#define _ULONG_MAX            0xffffffffffffffffULL
#define _ULONG_MIN            0

#define CHAR_BIT              8
#define CHAR_MAX              SCHAR_MAX
#define CHAR_MIN              SCHAR_MIN
#define INT_MAX               2147483647
#define INT_MIN               (-2147483647-1)
#define LONG_MAX              0x7fffffffffffffffLL
#define LONG_MIN              (-0x7fffffffffffffffLL-1LL)
#define SCHAR_MAX             127
#define SCHAR_MIN             (-127-1)
#define SHRT_MAX              32767
#define SHRT_MIN              (-32767-1)
#define UCHAR_MAX             255
#define USHRT_MAX             0xffff //65535
#define UINT_MAX              0xffffffffU
#define ULONG_MAX             0xffffffffffffffffULL

#define FLT_DIG               6 
#define FLT_MANT_DIG          24 
#define FLT_MAX_10_EXP        +38 
#define FLT_MAX_EXP           +128 
#define FLT_MIN_10_EXP        -37 
#define FLT_MIN_EXP           -125 
#define FLT_RADIX             2 
#define FLT_MAX               0x1.fffffep127f 
#define FLT_MIN               0x1.0p-126f 
#define FLT_EPSILON           0x1.0p-23f

#define HALF_DIG              3
#define HALF_MANT_DIG         11
#define HALF_MAX_10_EXP       +4
#define HALF_MAX_EXP          +16
#define HALF_MIN_10_EXP       -4
#define HALF_MIN_EXP          -13
#define HALF_RADIX            2
#define HALF_MAX              65504//0x1.ffcp15h
#define HALF_MIN              0x1.0p-14f
#define HALF_EPSILON          0x1.0p-10f

#define DBL_DIG              15
#define DBL_MANT_DIG         53
#define DBL_MAX_10_EXP       308
#define DBL_MAX_EXP          1024
#define DBL_MIN_10_EXP       (-307)
#define DBL_MIN_EXP          (-1021)
#define DBL_RADIX            2
#define DBL_MAX              1.7976931348623158e+308
#define DBL_MIN              2.2250738585072014e-308
#define DBL_EPSILON          2.2204460492503131e-016

#define M_E_F                 2.718281828459045f
#define M_LOG2E_F             1.442695040888963f
#define M_LOG10E_F            0.43429449200630f
#define M_LN2_F               0.693147180559945f
#define M_LN10_F              2.30258512496948f
#define M_PI_F                3.14159274101257f
#define M_PI_2_F              1.57079637050629f
#define M_PI_4_F              0.78539818525314f

#define M_1_PI_F              0.31830987334251f
#define M_2_PI_F              0.63661974668503f
#define M_2_SQRTPI_F          1.12837922573090f
#define M_SQRT2_F             1.41421353816986f
#define M_SQRT1_2_F           0.70710676908493f
#define M_LOG2_FLT_MAX        422.884867964704f

#define M_E			   		  			2.718281828459045235360287471
#define M_LOG2E               1.44269504088896340735992468100189214
#define M_LOG10E              0.434294481903251816668
#define M_LN2                 0.693147180559945309417232121458176568
#define M_LN10                2.302585092994045901094

#define M_1_PI 								0.318309886183790691216
#define M_2_PI 								0.636619772367581382433
#define M_2_SQRTPI            1.128379167095512558561
#define M_SQRT2               1.414213562373095145475
#define M_SQRT1_2             0.707106781186547572737

#define M_E_H                 2.71828174591064f
#define M_LOG2E_H             1.442695040888963387f
#define M_LOG10E_H            0.43429449200630f
#define M_LOG2_H			  			0.30102999566398119521373889472449f
#define M_LOG2_10_H			  		3.3219280948873623478703194294894f
#define M_LN2_H               0.69314718246460f
#define M_LN10_H              2.30258512496948f
#define M_PI_H                3.14159274101257f
#define M_PI_2_H              1.57079637050629f
#define M_PI_4_H              0.78539818525314f
#define M_1_PI_H              0.31830987334251f
#define M_2_PI_H              0.63661974668503f
#define M_2_SQRTPI_H          1.12837922573090f
#define M_SQRT2_H             1.41421353816986f
#define M_SQRT1_2_H           0.70710676908493f


#define FP_ILOGB0             INT_MIN
#define FP_ILOGBNAN           INT_MIN

#define MAXFLOAT           	  FLT_MAX
#define INFINITY			 (FLT_MAX + FLT_MAX)
#define NAN  			     (INFINITY - INFINITY)
#define HUGE_VALF            INFINITY

#define HALF_INFINITY        (HALF_MAX + HALF_MAX)

#define DBL_INFINITY		 (DBL_MAX + DBL_MAX)
#define HUGE_VAL             DBL_INFINITY

#ifndef __ENDIAN_LITTLE__
#define __ENDIAN_LITTLE__     1
#endif

#ifndef CL_VERSION_1_0
#define CL_VERSION_1_0 100
#endif

#ifndef CL_VERSION_1_1
#define CL_VERSION_1_1 110
#endif

#ifndef CL_VERSION_1_2
#define CL_VERSION_1_2 120
#endif

#ifndef CL_VERSION_2_0
#define CL_VERSION_2_0 200
#endif
   
#ifndef __OPENCL_VERSION__
#define __OPENCL_VERSION__    120
#endif

#ifndef __OPENCL_C_VERSION__
#define __OPENCL_C_VERSION__  120
#endif

#ifndef __kernel_exec
#define __kernel_exec(X, typen)  __kernel __attribute__((work_group_size_hint(X, 1, 1))) __attribute__((vec_type_hint(typen)))
#endif

#ifndef __ROUNDING_MODE__
#define __ROUNDING_MODE__ "rte"
#endif



