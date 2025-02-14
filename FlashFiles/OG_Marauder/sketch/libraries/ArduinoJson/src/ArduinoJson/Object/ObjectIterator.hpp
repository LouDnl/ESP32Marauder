#line 1 "E:\\workspaces\\ArduinoIDE\\ESP32Marauder\\esp32_marauder\\libraries\\ArduinoJson\\src\\ArduinoJson\\Object\\ObjectIterator.hpp"
// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Object/Pair.hpp>
#include <ArduinoJson/Variant/SlotFunctions.hpp>

namespace ARDUINOJSON_NAMESPACE {

class PairPtr {
 public:
  PairPtr(MemoryPool* pool, VariantSlot* slot) : _pair(pool, slot) {}

  const Pair* operator->() const {
    return &_pair;
  }

  const Pair& operator*() const {
    return _pair;
  }

 private:
  Pair _pair;
};

class ObjectIterator {
  friend class ObjectRef;

 public:
  ObjectIterator() : _slot(0) {}

  explicit ObjectIterator(MemoryPool* pool, VariantSlot* slot)
      : _pool(pool), _slot(slot) {}

  Pair operator*() const {
    return Pair(_pool, _slot);
  }
  PairPtr operator->() {
    return PairPtr(_pool, _slot);
  }

  bool operator==(const ObjectIterator& other) const {
    return _slot == other._slot;
  }

  bool operator!=(const ObjectIterator& other) const {
    return _slot != other._slot;
  }

  ObjectIterator& operator++() {
    _slot = _slot->next();
    return *this;
  }

  ObjectIterator& operator+=(size_t distance) {
    _slot = _slot->next(distance);
    return *this;
  }

 private:
  MemoryPool* _pool;
  VariantSlot* _slot;
};

class PairConstPtr {
 public:
  PairConstPtr(const VariantSlot* slot) : _pair(slot) {}

  const PairConst* operator->() const {
    return &_pair;
  }

  const PairConst& operator*() const {
    return _pair;
  }

 private:
  PairConst _pair;
};

class ObjectConstIterator {
  friend class ObjectRef;

 public:
  ObjectConstIterator() : _slot(0) {}

  explicit ObjectConstIterator(const VariantSlot* slot) : _slot(slot) {}

  PairConst operator*() const {
    return PairConst(_slot);
  }
  PairConstPtr operator->() {
    return PairConstPtr(_slot);
  }

  bool operator==(const ObjectConstIterator& other) const {
    return _slot == other._slot;
  }

  bool operator!=(const ObjectConstIterator& other) const {
    return _slot != other._slot;
  }

  ObjectConstIterator& operator++() {
    _slot = _slot->next();
    return *this;
  }

  ObjectConstIterator& operator+=(size_t distance) {
    _slot = _slot->next(distance);
    return *this;
  }

 private:
  const VariantSlot* _slot;
};
}  // namespace ARDUINOJSON_NAMESPACE
