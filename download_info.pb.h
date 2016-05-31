// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: download_info.proto

#ifndef PROTOBUF_download_5finfo_2eproto__INCLUDED
#define PROTOBUF_download_5finfo_2eproto__INCLUDED

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

namespace download {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_download_5finfo_2eproto();
void protobuf_AssignDesc_download_5finfo_2eproto();
void protobuf_ShutdownFile_download_5finfo_2eproto();

class DownloadInfo;
class Peer;

// ===================================================================

class DownloadInfo : public ::google::protobuf::Message {
 public:
  DownloadInfo();
  virtual ~DownloadInfo();

  DownloadInfo(const DownloadInfo& from);

  inline DownloadInfo& operator=(const DownloadInfo& from) {
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
  static const DownloadInfo& default_instance();

  void Swap(DownloadInfo* other);

  // implements Message ----------------------------------------------

  DownloadInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DownloadInfo& from);
  void MergeFrom(const DownloadInfo& from);
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

  // required int64 file_byte_size = 2;
  inline bool has_file_byte_size() const;
  inline void clear_file_byte_size();
  static const int kFileByteSizeFieldNumber = 2;
  inline ::google::protobuf::int64 file_byte_size() const;
  inline void set_file_byte_size(::google::protobuf::int64 value);

  // repeated .download.Peer peer_info = 1;
  inline int peer_info_size() const;
  inline void clear_peer_info();
  static const int kPeerInfoFieldNumber = 1;
  inline const ::download::Peer& peer_info(int index) const;
  inline ::download::Peer* mutable_peer_info(int index);
  inline ::download::Peer* add_peer_info();
  inline const ::google::protobuf::RepeatedPtrField< ::download::Peer >&
      peer_info() const;
  inline ::google::protobuf::RepeatedPtrField< ::download::Peer >*
      mutable_peer_info();

  // @@protoc_insertion_point(class_scope:download.DownloadInfo)
 private:
  inline void set_has_file_byte_size();
  inline void clear_has_file_byte_size();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int64 file_byte_size_;
  ::google::protobuf::RepeatedPtrField< ::download::Peer > peer_info_;
  friend void  protobuf_AddDesc_download_5finfo_2eproto();
  friend void protobuf_AssignDesc_download_5finfo_2eproto();
  friend void protobuf_ShutdownFile_download_5finfo_2eproto();

  void InitAsDefaultInstance();
  static DownloadInfo* default_instance_;
};
// -------------------------------------------------------------------

class Peer : public ::google::protobuf::Message {
 public:
  Peer();
  virtual ~Peer();

  Peer(const Peer& from);

  inline Peer& operator=(const Peer& from) {
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
  static const Peer& default_instance();

  void Swap(Peer* other);

  // implements Message ----------------------------------------------

  Peer* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Peer& from);
  void MergeFrom(const Peer& from);
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

  // required string ip = 1;
  inline bool has_ip() const;
  inline void clear_ip();
  static const int kIpFieldNumber = 1;
  inline const ::std::string& ip() const;
  inline void set_ip(const ::std::string& value);
  inline void set_ip(const char* value);
  inline void set_ip(const char* value, size_t size);
  inline ::std::string* mutable_ip();
  inline ::std::string* release_ip();
  inline void set_allocated_ip(::std::string* ip);

  // required int32 port = 2;
  inline bool has_port() const;
  inline void clear_port();
  static const int kPortFieldNumber = 2;
  inline ::google::protobuf::int32 port() const;
  inline void set_port(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:download.Peer)
 private:
  inline void set_has_ip();
  inline void clear_has_ip();
  inline void set_has_port();
  inline void clear_has_port();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* ip_;
  ::google::protobuf::int32 port_;
  friend void  protobuf_AddDesc_download_5finfo_2eproto();
  friend void protobuf_AssignDesc_download_5finfo_2eproto();
  friend void protobuf_ShutdownFile_download_5finfo_2eproto();

  void InitAsDefaultInstance();
  static Peer* default_instance_;
};
// ===================================================================


// ===================================================================

// DownloadInfo

// required int64 file_byte_size = 2;
inline bool DownloadInfo::has_file_byte_size() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void DownloadInfo::set_has_file_byte_size() {
  _has_bits_[0] |= 0x00000001u;
}
inline void DownloadInfo::clear_has_file_byte_size() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void DownloadInfo::clear_file_byte_size() {
  file_byte_size_ = GOOGLE_LONGLONG(0);
  clear_has_file_byte_size();
}
inline ::google::protobuf::int64 DownloadInfo::file_byte_size() const {
  // @@protoc_insertion_point(field_get:download.DownloadInfo.file_byte_size)
  return file_byte_size_;
}
inline void DownloadInfo::set_file_byte_size(::google::protobuf::int64 value) {
  set_has_file_byte_size();
  file_byte_size_ = value;
  // @@protoc_insertion_point(field_set:download.DownloadInfo.file_byte_size)
}

// repeated .download.Peer peer_info = 1;
inline int DownloadInfo::peer_info_size() const {
  return peer_info_.size();
}
inline void DownloadInfo::clear_peer_info() {
  peer_info_.Clear();
}
inline const ::download::Peer& DownloadInfo::peer_info(int index) const {
  // @@protoc_insertion_point(field_get:download.DownloadInfo.peer_info)
  return peer_info_.Get(index);
}
inline ::download::Peer* DownloadInfo::mutable_peer_info(int index) {
  // @@protoc_insertion_point(field_mutable:download.DownloadInfo.peer_info)
  return peer_info_.Mutable(index);
}
inline ::download::Peer* DownloadInfo::add_peer_info() {
  // @@protoc_insertion_point(field_add:download.DownloadInfo.peer_info)
  return peer_info_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::download::Peer >&
DownloadInfo::peer_info() const {
  // @@protoc_insertion_point(field_list:download.DownloadInfo.peer_info)
  return peer_info_;
}
inline ::google::protobuf::RepeatedPtrField< ::download::Peer >*
DownloadInfo::mutable_peer_info() {
  // @@protoc_insertion_point(field_mutable_list:download.DownloadInfo.peer_info)
  return &peer_info_;
}

// -------------------------------------------------------------------

// Peer

// required string ip = 1;
inline bool Peer::has_ip() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Peer::set_has_ip() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Peer::clear_has_ip() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Peer::clear_ip() {
  if (ip_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    ip_->clear();
  }
  clear_has_ip();
}
inline const ::std::string& Peer::ip() const {
  // @@protoc_insertion_point(field_get:download.Peer.ip)
  return *ip_;
}
inline void Peer::set_ip(const ::std::string& value) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
  // @@protoc_insertion_point(field_set:download.Peer.ip)
}
inline void Peer::set_ip(const char* value) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    ip_ = new ::std::string;
  }
  ip_->assign(value);
  // @@protoc_insertion_point(field_set_char:download.Peer.ip)
}
inline void Peer::set_ip(const char* value, size_t size) {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    ip_ = new ::std::string;
  }
  ip_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:download.Peer.ip)
}
inline ::std::string* Peer::mutable_ip() {
  set_has_ip();
  if (ip_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    ip_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:download.Peer.ip)
  return ip_;
}
inline ::std::string* Peer::release_ip() {
  clear_has_ip();
  if (ip_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = ip_;
    ip_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void Peer::set_allocated_ip(::std::string* ip) {
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
  // @@protoc_insertion_point(field_set_allocated:download.Peer.ip)
}

// required int32 port = 2;
inline bool Peer::has_port() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Peer::set_has_port() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Peer::clear_has_port() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Peer::clear_port() {
  port_ = 0;
  clear_has_port();
}
inline ::google::protobuf::int32 Peer::port() const {
  // @@protoc_insertion_point(field_get:download.Peer.port)
  return port_;
}
inline void Peer::set_port(::google::protobuf::int32 value) {
  set_has_port();
  port_ = value;
  // @@protoc_insertion_point(field_set:download.Peer.port)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace download

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_download_5finfo_2eproto__INCLUDED
