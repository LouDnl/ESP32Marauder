#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\src\\ArduinoJson\\Variant\\VariantAttorney.hpp"
// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Polyfills/attributes.hpp>
#include <ArduinoJson/Polyfills/type_traits.hpp>
#include <ArduinoJson/Variant/VariantTo.hpp>
#include "VariantConstRef.hpp"

namespace ARDUINOJSON_NAMESPACE {

// Grants access to the internal variant API
class VariantAttorney {
  // Tells whether getData() returns a const pointer
  template <typename TClient>
  struct ResultOfGetData {
   protected:  // <- to avoid GCC's "all member functions in class are private"
    typedef char Yes[1];
    typedef char No[2];

    static Yes& probe(const VariantData*);
    static No& probe(VariantData*);

    static TClient& client;

   public:
    typedef typename conditional<sizeof(probe(client.getData())) == sizeof(Yes),
                                 const VariantData*, VariantData*>::type type;
  };

 public:
  template <typename TClient>
  FORCE_INLINE static MemoryPool* getPool(TClient& client) {
    return client.getPool();
  }

  template <typename TClient>
  FORCE_INLINE static typename ResultOfGetData<TClient>::type getData(
      TClient& client) {
    return client.getData();
  }

  template <typename TClient>
  FORCE_INLINE static VariantData* getOrCreateData(TClient& client) {
    return client.getOrCreateData();
  }
};

}  // namespace ARDUINOJSON_NAMESPACE
