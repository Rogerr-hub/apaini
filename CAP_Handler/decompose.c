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
    uint16_t size;
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
    cp_info constant_pool[100];
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
    uint16_t signature_pool_length; //versi 3.1
    type_descriptor signature_pool[50]; //versi 3.1
    interface_info interfaces[50];
    class_info_compact classes[50]; //versi 3.1
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
    uint8_t offsets_to_byte_indices[50];
    uint16_t byte2_index_count;
    uint8_t offsets_to_byte2_indices[50];
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

void import_structure_versi_2_1(uint8_t *buffer, size_t length, import *imp) {
    size_t offset = 0; // Tracks the current buffer position

    // Ensure minimum buffer size
    if (length < 4) return;

    // Extract 'tag' (1 byte)
    imp->tag = buffer[offset++];

    // Extract 'size' (2 bytes, big-endian)
    imp->size = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;

    // Extract 'count' (1 byte)
    imp->count = buffer[offset++];

    // Limit 'count' to 5 to avoid buffer overflows
    if (imp->count > 5) imp->count = 5;

    // Extract package information for each package
    for (int i = 0; i < imp->count; i++) {
        // Extract 'minor' and 'major' (1 byte each)
        imp->packages[i].minor = buffer[offset++];
        imp->packages[i].major = buffer[offset++];

        // Extract 'AID_length' (1 byte)
        imp->packages[i].AID_length = buffer[offset++];

        // Limit 'AID_length' to 10 to avoid overflow
        if (imp->packages[i].AID_length > 10) imp->packages[i].AID_length = 10;

        // Extract AID array
        for (int j = 0; j < imp->packages[i].AID_length; j++) {
            imp->packages[i].AID[j] = buffer[offset++];
        }
    }
}


void cp_structure_versi_2_1(uint8_t* buffer, size_t length, constantpool* cp) {
    size_t offset = 0; // Tracks the current position in the buffer

    // Ensure buffer has the minimum required size
    if (length < 5) return;

    // Extract 'tag' (1 byte)
    cp->tag = buffer[offset++];

    // Extract 'size' (2 bytes, big-endian)
    cp->size = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;

    // Extract 'count' (2 bytes, big-endian)
    cp->count = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;

    // Limit 'count' to 100 to prevent buffer overflow
    if (cp->count > 100) cp->count = 100;

    // Extract each constant pool entry
    for (int i = 0; i < cp->count; i++) {
        // Extract 'tag' (1 byte) for each constant pool entry
        cp->constant_pool[i].tag = buffer[offset++];

        // Extract 'info' (3 bytes)
        for (int j = 0; j < 3; j++) {
            cp->constant_pool[i].info[j] = buffer[offset++];
        }
    }
}

void sf_structure_versi_2_1(uint8_t* buffer, size_t length, static_field* sf) {
    size_t offset = 0;

    // Ensure buffer has enough data to parse the required fields
    if (length < 11) return;

    // Extract 'tag' (1 byte)
    sf->tag = buffer[offset++];

    // Extract 'size' (2 bytes, big-endian)
    sf->size = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;

    // Extract 'image_size' (2 bytes, big-endian)
    sf->image_size = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;

    // Extract 'reference_count' (2 bytes, big-endian)
    sf->reference_count = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;

    // Extract 'array_init_count' (2 bytes, big-endian)
    sf->array_init_count = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;

    // Limit array_init_count to 10 to avoid overflow
    if (sf->array_init_count > 10) sf->array_init_count = 10;

    // Extract 'array_init' entries
    for (int i = 0; i < sf->array_init_count; i++) {
        // Extract 'type' (1 byte)
        sf->array_init[i].type = buffer[offset++];

        // Extract 'count' (2 bytes, big-endian)
        sf->array_init[i].count = (buffer[offset] << 8) | buffer[offset + 1];
        offset += 2;

        // Extract 'values' (up to 10 bytes)
        for (int j = 0; j < 10; j++) {
            sf->array_init[i].values[j] = buffer[offset++];
        }
    }

    // Extract 'default_value_count' (2 bytes, big-endian)
    sf->default_value_count = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;

    // Extract 'non_default_value_count' (2 bytes, big-endian)
    if(sf->non_default_value_count!=0){
        sf->non_default_value_count = (buffer[offset] << 8) | buffer[offset + 1];
        offset += 2;

        // Extract 'non_default_values' (up to 10 bytes)
        for (int i = 0; i < 10; i++) {
            sf->non_default_values[i] = buffer[offset++];
        }
    }
    
}

void reflo_structure_versi_2_1(uint8_t* buffer, size_t length, RefLocation* rf) {
    size_t offset = 0;

    // Ensure buffer is large enough to parse initial fields
    if (length < 7) return;

    // Extract 'tag' (1 byte)
    rf->tag = buffer[offset++];

    // Extract 'size' (2 bytes, big-endian)
    rf->size = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;

    // Extract 'byte_index_count' (2 bytes, big-endian)
    rf->byte_index_count = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;

    // Extract 'offsets_to_byte_indices' (up to 10 bytes)
    for (int i = 0; i < 50; i++) {
        if (i < rf->byte_index_count) {
            rf->offsets_to_byte_indices[i] = buffer[offset++];
        } else {
            rf->offsets_to_byte_indices[i] = 0;  // Fill unused slots with zero
        }
    }

    // Extract 'byte2_index_count' (2 bytes, big-endian)
    rf->byte2_index_count = (buffer[offset] << 8) | buffer[offset + 1];
    offset += 2;

    // Extract 'offsets_to_byte2_indices' (up to 10 bytes)
    for (int i = 0; i < 50; i++) {
        if (i < rf->byte2_index_count) {
            rf->offsets_to_byte2_indices[i] = buffer[offset++];
        } else {
            rf->offsets_to_byte2_indices[i] = 0;  // Fill unused slots with zero
        }
    }
}


// int main(){
//     uint8_t data[256];
//     size_t length = 0;
//     applet app;
//     directory drt;
//     header hdr;
//     import imp;
//     constantpool cp;
//     static_field sf;
//     RefLocation rf;

//     read_isi_partisi("jcard.cap", "RefLocation.cap", data, &length);
//     //cp_structure_versi_2_1(data, length, &cp);
//     reflo_structure_versi_2_1(data, length, &rf);
//     // Print parsed data
//     printf("Tag: %02x\n", rf.tag);
//     printf("Size: %04x\n", rf.size);
//     printf("Byte Index Count: %04x\n", rf.byte_index_count);
//     printf("Offsets to Byte Indices: ");
//     for (int i = 0; i < rf.byte_index_count; i++) {
//         printf("%02x ", rf.offsets_to_byte_indices[i]);
//     }
//     printf("\n");

//     printf("Byte2 Index Count: %04x\n", rf.byte2_index_count);
//     printf("Offsets to Byte2 Indices: ");
//     for (int i = 0; i < rf.byte2_index_count; i++) {
//         printf("%02x ", rf.offsets_to_byte2_indices[i]);
//     }
//     printf("\n");


//     return 0;

   
// }
