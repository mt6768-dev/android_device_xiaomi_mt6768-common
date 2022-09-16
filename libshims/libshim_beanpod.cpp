#include <keymaster/android_keymaster_messages.h>

extern "C" {
void _ZN9keymaster19GenerateKeyResponseD1Ev() {}
void _ZN9keymaster17AttestKeyResponseD1Ev() {}
void _ZN9keymaster16ImportKeyRequest14SetKeyMaterialEPKvm(keymaster::ImportKeyRequest* thisptr, const uint8_t* key_material, size_t length) {
	thisptr->key_data = keymaster::KeymasterKeyBlob(key_material, length);
}
}
