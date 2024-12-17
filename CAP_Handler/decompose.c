#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
//#include "utils.h"


//=========Header=======================//
typedef struct package_info
{
    uint8_t minor;
    uint8_t major;
    uint8_t AID_length;
    uint8_t AID[10];
} package_info;

typedef struct package_name_info
{
    uint8_t name_length;
    uint8_t name[100];
} package_name_info;

typedef struct header
{
    uint8_t tag;
    uint16_t size;
    uint32_t magic;
    uint8_t minor;
    uint8_t major;
    uint8_t flags;
    package_info package;
    package_name_info package_name;

} header;
//==========Header================//

//==========Directory=============//
typedef struct component_size_info_compact
{
    uint16_t Header_Component_Size;
    uint16_t Directory_Component_Size;
    uint16_t Applet_Component_Size;
    uint16_t Import_Component_Size;
    uint16_t Constant_Pool_Component_Size;
    uint16_t Class_Component_Size;
    uint16_t Method_Component_Size;
    uint16_t Static_Field_Component_Size;
    uint16_t Reference_Location_Component_Size;
    uint16_t Export_Component_Size;
    uint16_t Decriptor_Component_Size;
} component_size_info_compact ;
 
typedef struct static_field_size_info
{
    uint16_t image_size;
    uint16_t array_init_count;
    uint16_t array_init_size;
} static_field_size_info ;

typedef struct directory
{
    uint8_t tag;
    uint16_t size;
    uint16_t component_sizes1[11]; //versi 2.1
    component_size_info_compact component_sizes; //versi 3.1
    static_field_size_info static_field_size; 
    uint8_t import_count;
    uint8_t applet_count;
    uint8_t custom_count;
} directory ;

//==========Directory============//

//===========Applet==============//

typedef struct applets
{
    uint8_t AID_length;
    uint8_t AID[10];
    uint16_t install_method_offset;
} applets ;


typedef struct applet
{
    uint8_t tag;
    uint16_t size;
    uint8_t count;
    applets applets[5];
} applet ;

//===========Applet==============//

//===========Import==============//

typedef struct import
{
    uint8_t tag;
    uint16_t size_t;
    uint8_t count;
    package_info packages[5];
} import;

//===========Import==============//

//======Constan_Pool=============//
//CONSTANT
const uint8_t CONSTANT_Classref = 0x01;
const uint8_t CONSTANT_InstanceFieldref = 0x02;
const uint8_t CONSTANT_VirtualMethodref = 0x03;
const uint8_t CONSTANT_SuperMethodref = 0x04;
const uint8_t CONSTANT_StaticFieldref = 0x05;
const uint8_t CONSTANT_StaticMethodref = 0x06;

typedef struct external_class_ref
{
    uint8_t package_token;
    uint8_t class_token;
} external_class_ref;

typedef struct class_ref
{
    uint16_t internal_class_ref;
    external_class_ref external_class_ref;
} class_ref;

typedef struct CONSTANT_Classref_info
{
    uint8_t tag;
    class_ref class_ref;
    uint8_t padding;

} CONSTANT_Classref_info;

typedef struct CONSTANT_InstanceFieldref_info
{
    uint8_t tag;
    class_ref class;
    uint8_t token;
} CONSTANT_InstanceFieldref_info;

typedef struct CONSTANT_VirtualMethodref_info
{
    uint8_t tag;
    class_ref class;
    uint8_t token;
} CONSTANT_VirtualMethodref_info;

typedef struct CONSTANT_SuperMethodref_info
{
    uint8_t tag;
    class_ref class;
    uint8_t token;
} CONSTANT_SuperMethodref_info;

typedef struct internal_ref
{
    uint8_t padding;;
    uint16_t offset;
} internal_ref;

typedef struct external_ref
{
    uint8_t package_token;
    uint8_t class_token;
    uint8_t token;
} external_ref;

typedef struct static_field_ref
{   
    internal_ref internal_ref;
    external_ref external_ref;
} static_field_ref;


typedef struct CONSTANT_StaticFieldref_info
{
    uint8_t tag;
    static_field_ref static_field_ref;
} CONSTANT_StaticFieldref_info;

typedef struct static_method_ref
{
    internal_ref internal_ref;
    external_ref external_ref;
} static_method_ref;

typedef struct CONSTANT_StaticMethodref_info
{
    uint8_t tag;
    static_method_ref static_method_ref;
} CONSTANT_StaticMethodref_info;


typedef struct cp_info
{
    uint8_t tag;
    uint8_t info[3];
} cp_info ;

typedef struct constantpool
{
    uint8_t tag;
    uint16_t size;
    uint16_t count;
    cp_info constant_pool[5];
} constantpool ;

//======Constan_Pool=============//


//======Class====================//
/*
Struct buat class
*/
typedef struct interface_name_info
{
    /* data */
} interface_name_info ;

typedef struct type_descriptor
{
    uint8_t nibble_count;
    uint8_t type[31];
} type_descriptor ;

typedef struct interface_info
{
    uint8_t bitfield; // bit[4] = flags, bit[4] = interface_count
    class_ref superinterfaces[20];
    interface_name_info interface_name;
} interface_info ;

typedef struct class_info_compact
{
    /* data */
} class_info_compact ;


typedef struct class
{
    uint8_t tag;
    uint16_t size;
    uint16_t signature_pool_length;
    type_descriptor signature_pool[50];
    interface_info interfaces[50];
    class_info_compact classes[50];
} class ;

//======Class====================//


//=======Method=================//
/*
Struct buat Method
*/
typedef struct method_header_info
{
    uint8_t bitfield; // bit[4] = flags, bit[4] = max_stack
    uint8_t bifield2; // bit[4] = nargs, bit[4] = max_locals
} method_header_info ;


typedef struct method_info
{
    method_header_info method_header;
    uint8_t bytecodes[100];
} method_info ;


typedef struct exception_handler_info
{
    uint16_t start_offset;
    uint16_t bitfield; // bit[1] = stop bit. bit[15] = active_length
    uint16_t handler_offset;
    uint16_t catch_type_index;
} exception_handler_info ;


typedef struct method
{
    uint8_t tag;
    uint16_t size;
    uint8_t handler_count;
    exception_handler_info exception_handlers[20];
    method_info methods[20];
} method ;

//=======Method=================//


//=======StaticField============//
/*
Struct buat SF
*/
typedef struct array_init_info
{
    uint8_t type; 
    uint16_t count;
    uint8_t values[10];
} array_init_info  ;


typedef struct static_field
{
    uint8_t tag;
    uint16_t size;
    uint16_t image_size;
    uint16_t reference_count;
    uint16_t array_init_count;
    array_init_info array_init[10];
    uint16_t default_value_count;
    uint16_t non_default_value_count;
    uint8_t non_default_values[10];
} static_field ;

//=======StaticField============//


//=========ReferenceLocation=======//
/*
Struct buat RefLoc
*/
typedef struct RefLocation
{
    /* data */
    uint8_t tag;
    uint16_t size;
    uint16_t byte_index_count;
    uint8_t offsets_to_byte_indices[10];
    uint16_t byte2_index_count;
    uint8_t offsets_to_byte2_indices[10];
} RefLocation;

//=========ReferenceLocation=======//

//==========Export==================//
/*
Struct buat Export
*/
//==========Export==================//

//==========Descriptor==============//
/*
Struct buat descriptor
*/
typedef struct field_ref
{
    static_field_ref static_field;
    CONSTANT_InstanceFieldref_info instance_field;
} field_ref;
typedef struct type
{
    uint16_t primitive_type;
    uint16_t reference_type;
} type;


typedef struct field_descriptor_info
{
    uint8_t token;
    uint8_t access_flags;
    field_ref union1;
    type union2;
    
} field_descriptor_info;

typedef struct method_descriptor_info
{
    /* data */
} method_descriptor_info;

typedef struct class_descriptor_info
{
    uint8_t token;
    uint8_t access_flags;
    class_ref this_class_ref;
    uint8_t interface_count;
    uint16_t field_count;
    uint16_t method_count;
    class_ref interfaces[10];
    field_descriptor_info fields[10];
    method_descriptor_info methods[10];
} class_descriptor_info;


typedef struct type_descriptor_info
{
    
} type_descriptor_info ;


typedef struct descriptor
{
    uint8_t tag;
    uint16_t size;
    uint8_t class_count;
    class_descriptor_info classes[10];
    type_descriptor_info types;
} descriptor ;

//==========Descriptor==============//

void header_structure(uint8_t *buffer, size_t length, header *hdr) {
    size_t offset = 0; // Tracks the current buffer position

    // Ensure minimum buffer size
    if (length < 12) return;

    // Extract 'tag' (1 byte)
    hdr->tag = buffer[offset++];

    // Extract 'size' (2 bytes, big-endian)
    hdr->size = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;

    // Extract 'magic' (4 bytes, big-endian)
    hdr->magic = (buffer[offset] << 24) | (buffer[offset + 1] << 16) | (buffer[offset + 2] << 8) | buffer[offset + 3];
    offset += 4;

    // Extract 'minor', 'major', and 'flags' (1 byte each)
    hdr->minor = buffer[offset++];
    hdr->major = buffer[offset++];
    hdr->flags = buffer[offset++];

    // Extract 'package_info'
    hdr->package.minor = buffer[offset++];
    hdr->package.major = buffer[offset++];
    hdr->package.AID_length = buffer[offset++];

    // Extract 'AID' array (up to 10 bytes)
    if (hdr->package.AID_length > 10) hdr->package.AID_length = 10; // Prevent buffer overflow
    for (int i = 0; i < hdr->package.AID_length; i++) {
        hdr->package.AID[i] = buffer[offset++];
    }

    // Extract 'package_name_info'
    // hdr->package_name.name_length = buffer[offset++];
    // if (hdr->package_name.name_length > 100) hdr->package_name.name_length = 100; // Prevent overflow
    // for (int i = 0; i < hdr->package_name.name_length; i++) {
    //     hdr->package_name.name[i] = buffer[offset++];
    // }
}


void applet_structure_versi_2_1(uint8_t *buffer, size_t length, applet *aplt) {
    size_t offset = 0;

    if (length < 4) return; // Ensure buffer has minimum required bytes

    // Extract tag (1 byte)
    aplt->tag = buffer[offset++];
    
    // Extract size (2 bytes, big-endian)
    aplt->size = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;

    // Extract count (1 byte)
    aplt->count = buffer[offset++];
    if (aplt->count > 5) return; // Cap count to 5 (as per struct definition)

    // Parse each applet
    for (int i = 0; i < aplt->count; i++) {
        // Extract AID_length (1 byte)
        aplt->applets[i].AID_length = buffer[offset++];
        
        // Extract AID (up to 10 bytes)
        memset(aplt->applets[i].AID, 0, sizeof(aplt->applets[i].AID)); // Clear AID
        if (aplt->applets[i].AID_length > 10) aplt->applets[i].AID_length = 10; // Cap length
        memcpy(aplt->applets[i].AID, &buffer[offset], aplt->applets[i].AID_length);
        offset += aplt->applets[i].AID_length;

        // Extract install_method_offset (2 bytes, big-endian)
        if (offset + 1 >= length) return; // Ensure enough buffer for offset
        aplt->applets[i].install_method_offset = (buffer[offset] << 8) | buffer[offset + 1];
        offset += 2;
    }
}

void directory_structure_versi_2_1(uint8_t *buffer, size_t length, directory *drt) {
    size_t offset = 0;

    // Ensure buffer has minimum required bytes
    if (length < 4) return;

    // Extract 'tag' (1 byte)
    drt->tag = buffer[offset++];

    // Extract 'size' (2 bytes, big-endian)
    drt->size = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;

    // Extract 'component_sizes1' (11 x 2 bytes, big-endian)
    for (int i = 0; i < 11; i++) {
        if (offset + 1 >= length) return; // Check buffer safety
        drt->component_sizes1[i] = (buffer[offset] << 8) | buffer[offset + 1];
        offset += 2;
    }

    // Extract 'static_field_size' fields (3 x 2 bytes, big-endian)
    if (offset + 5 >= length) return; // Ensure enough buffer for 3 fields (6 bytes total)
    drt->static_field_size.image_size = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;
    drt->static_field_size.array_init_count = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;
    drt->static_field_size.array_init_size = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;

    // Extract 'import_count', 'applet_count', and 'custom_count' (1 byte each)
    if (offset + 2 >= length) return; // Ensure enough buffer for 3 bytes
    drt->import_count = buffer[offset++];
    drt->applet_count = buffer[offset++];
    drt->custom_count = buffer[offset++];
}



// int main(){
//     uint8_t data[256];
//     size_t length = 0;
//     read_isi_partisi("jcard.cap", "Header.cap", data, &length);
//     print_array(data, length);
//     applet app;
//     directory drt;
//     header hdr;
//     //directory_structure_versi_2_1(data, length, &drt);
//     header_structure(data, length, &hdr);



//     printf("Tag: %02x\n", hdr.tag);
//     printf("Size: %04x\n", hdr.size);
//     printf("Magic: %08x\n", hdr.magic);
//     printf("Minor: %02x, Major: %02x, Flags: %02x\n", hdr.minor, hdr.major, hdr.flags);

//     printf("Package Info:\n");
//     printf("  Minor: %02x, Major: %02x\n", hdr.package.minor, hdr.package.major);
//     printf("  AID Length: %02x\n", hdr.package.AID_length);
//     printf("  AID: ");
//     for (int i = 0; i < hdr.package.AID_length; i++) {
//         printf("%02x ", hdr.package.AID[i]);
//     }
//     printf("\n");

//     printf("\n");

   
// }