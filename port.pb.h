// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: port.proto

#ifndef PROTOBUF_port_2eproto__INCLUDED
#define PROTOBUF_port_2eproto__INCLUDED

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

namespace port {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_port_2eproto();
void protobuf_AssignDesc_port_2eproto();
void protobuf_ShutdownFile_port_2eproto();

class Port;

// ===================================================================

class Port : public ::google::protobuf::Message {
 public:
  Port();
  virtual ~Port();

  Port(const Port& from);

  inline Port& operator=(const Port& from) {
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
  static const Port& default_instance();

  void Swap(Port* other);

  // implements Message ----------------------------------------------

  Port* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Port& from);
  void MergeFrom(const Port& from);
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

  // required int32 port_num = 1;
  inline bool has_port_num() const;
  inline void clear_port_num();
  static const int kPortNumFieldNumber = 1;
  inline ::google::protobuf::int32 port_num() const;
  inline void set_port_num(::google::protobuf::int32 value);

  // required string ip = 2;
  inline bool has_ip() const;
  inline void clear_ip();
  static const int kIpFieldNumber = 2;
  inline const ::std::string& ip() const;
  inline void set_ip(const ::std::string& value);
  inline void set_ip(const char* value);
  inline void set_ip(const char* value, size_t size);
  inline ::std::string* mutable_ip();
  inline ::std::string* release_ip();
  inline void set_allocated_ip(::std::string* ip);

  // @@protoc_insertion_point(class_scope:port.Port)
 private:
  inline void set_has_port_num();
  inline void clear_has_port_num();
  inline void set_has_ip();
  inline void clear_has_ip();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* ip_;
  ::google::protobuf::int32 port_num_;
  friend void  protobuf_AddDesc_port_2eproto();
  friend void protobuf_AssignDesc_port_2eproto();
  friend void protobuf_ShutdownFile_port_2eproto();

  void InitAsDefaultInstance();
  static Port* default_instance_;
};
// ===================================================================


// ===================================================================

// Port

// required int32 port_num = 1;
inline bool Port::has_port_num() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Port::set_has_port_num() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Port::clear_has_port_num() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Port::clear_port_num() {
  port_num_ = 0;
  clear_has_port_num();
}
inline ::google::protobuf::int32 Port::port_num() const {
  // @@protoc_insertion_point(field_get:port.Port.port_num)
  return port_num_;
}
inline void Port::set_port_num(::google::protobuf::int32 value) {
  set_has_port_num();
  port_num_ = value;
  // @@protoc_insertion_point(field_set:port.Port.port_num)
}

// required string ip = 2;
inline bool Port::has_ip() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Port::set_has_ip() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Port::clear_has_ip() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Port::clear_ip() {
  if (ip_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    ip_->clear();
  }
  clear_has_ip();
}
inline const ::std::string& Port::ip() const {
  // @@protoc_insertion_point(field_get:port.Port.ip)
  return *ip_;
}
inline void Port::set_ip(const ::std::string& value) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
  // @@protoc_insertion_point(field_set:port.Port.ip)
}
inline void Port::set_ip(const char* value) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
  // @@protoc_insertion_point(field_set_char:port.Port.ip)
}
inline void Port::set_ip(const char* value, size_t size) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    ip_ = new ::std::string;
  }
  ip_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:port.Port.ip)
}
inline ::std::string* Port::mutable_ip() {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    ip_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:port.Port.ip)
  return ip_;
}
inline ::std::string* Port::release_ip() {
  clear_has_ip();
  if (ip_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = ip_;
    ip_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void Port::set_allocated_ip(::std::string* ip) {
  if (ip_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete ip_;
  }
  if (ip) {
    set_has_ip();
    ip_ = ip;
  } else {
    clear_has_ip();
    ip_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:port.Port.ip)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace port

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_port_2eproto__INCLUDED