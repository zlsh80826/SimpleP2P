// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: regist.proto

#ifndef PROTOBUF_regist_2eproto__INCLUDED
#define PROTOBUF_regist_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace regist {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_regist_2eproto();
void protobuf_AssignDesc_regist_2eproto();
void protobuf_ShutdownFile_regist_2eproto();

class Regist;

// ===================================================================

class Regist : public ::google::protobuf::Message {
 public:
  Regist();
  virtual ~Regist();

  Regist(const Regist& from);

  inline Regist& operator=(const Regist& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Regist& default_instance();

  void Swap(Regist* other);

  // implements Message ----------------------------------------------

  Regist* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Regist& from);
  void MergeFrom(const Regist& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline const ::std::string& id() const;
  inline void set_id(const ::std::string& value);
  inline void set_id(const char* value);
  inline void set_id(const char* value, size_t size);
  inline ::std::string* mutable_id();
  inline ::std::string* release_id();
  inline void set_allocated_id(::std::string* id);

  // required string passwd = 2;
  inline bool has_passwd() const;
  inline void clear_passwd();
  static const int kPasswdFieldNumber = 2;
  inline const ::std::string& passwd() const;
  inline void set_passwd(const ::std::string& value);
  inline void set_passwd(const char* value);
  inline void set_passwd(const char* value, size_t size);
  inline ::std::string* mutable_passwd();
  inline ::std::string* release_passwd();
  inline void set_allocated_passwd(::std::string* passwd);

  // @@protoc_insertion_point(class_scope:regist.Regist)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_passwd();
  inline void clear_has_passwd();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* id_;
  ::std::string* passwd_;
  friend void  protobuf_AddDesc_regist_2eproto();
  friend void protobuf_AssignDesc_regist_2eproto();
  friend void protobuf_ShutdownFile_regist_2eproto();

  void InitAsDefaultInstance();
  static Regist* default_instance_;
};
// ===================================================================


// ===================================================================

// Regist

// required string id = 1;
inline bool Regist::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Regist::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Regist::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Regist::clear_id() {
  if (id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    id_->clear();
  }
  clear_has_id();
}
inline const ::std::string& Regist::id() const {
  // @@protoc_insertion_point(field_get:regist.Regist.id)
  return *id_;
}
inline void Regist::set_id(const ::std::string& value) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    id_ = new ::std::string;
  }
  id_->assign(value);
  // @@protoc_insertion_point(field_set:regist.Regist.id)
}
inline void Regist::set_id(const char* value) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    id_ = new ::std::string;
  }
  id_->assign(value);
  // @@protoc_insertion_point(field_set_char:regist.Regist.id)
}
inline void Regist::set_id(const char* value, size_t size) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    id_ = new ::std::string;
  }
  id_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:regist.Regist.id)
}
inline ::std::string* Regist::mutable_id() {
  set_has_id();
  if (id_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    id_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:regist.Regist.id)
  return id_;
}
inline ::std::string* Regist::release_id() {
  clear_has_id();
  if (id_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = id_;
    id_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void Regist::set_allocated_id(::std::string* id) {
  if (id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete id_;
  }
  if (id) {
    set_has_id();
    id_ = id;
  } else {
    clear_has_id();
    id_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:regist.Regist.id)
}

// required string passwd = 2;
inline bool Regist::has_passwd() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Regist::set_has_passwd() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Regist::clear_has_passwd() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Regist::clear_passwd() {
  if (passwd_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    passwd_->clear();
  }
  clear_has_passwd();
}
inline const ::std::string& Regist::passwd() const {
  // @@protoc_insertion_point(field_get:regist.Regist.passwd)
  return *passwd_;
}
inline void Regist::set_passwd(const ::std::string& value) {
  set_has_passwd();
  if (passwd_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    passwd_ = new ::std::string;
  }
  passwd_->assign(value);
  // @@protoc_insertion_point(field_set:regist.Regist.passwd)
}
inline void Regist::set_passwd(const char* value) {
  set_has_passwd();
  if (passwd_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    passwd_ = new ::std::string;
  }
  passwd_->assign(value);
  // @@protoc_insertion_point(field_set_char:regist.Regist.passwd)
}
inline void Regist::set_passwd(const char* value, size_t size) {
  set_has_passwd();
  if (passwd_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    passwd_ = new ::std::string;
  }
  passwd_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:regist.Regist.passwd)
}
inline ::std::string* Regist::mutable_passwd() {
  set_has_passwd();
  if (passwd_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    passwd_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:regist.Regist.passwd)
  return passwd_;
}
inline ::std::string* Regist::release_passwd() {
  clear_has_passwd();
  if (passwd_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = passwd_;
    passwd_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void Regist::set_allocated_passwd(::std::string* passwd) {
  if (passwd_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete passwd_;
  }
  if (passwd) {
    set_has_passwd();
    passwd_ = passwd;
  } else {
    clear_has_passwd();
    passwd_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:regist.Regist.passwd)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace regist

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_regist_2eproto__INCLUDED
