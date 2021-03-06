// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: download_info.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "download_info.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace download {

namespace {

const ::google::protobuf::Descriptor* DownloadInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  DownloadInfo_reflection_ = NULL;
const ::google::protobuf::Descriptor* Peer_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Peer_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_download_5finfo_2eproto() {
  protobuf_AddDesc_download_5finfo_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "download_info.proto");
  GOOGLE_CHECK(file != NULL);
  DownloadInfo_descriptor_ = file->message_type(0);
  static const int DownloadInfo_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DownloadInfo, file_byte_size_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DownloadInfo, peer_info_),
  };
  DownloadInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      DownloadInfo_descriptor_,
      DownloadInfo::default_instance_,
      DownloadInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DownloadInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DownloadInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(DownloadInfo));
  Peer_descriptor_ = file->message_type(1);
  static const int Peer_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Peer, ip_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Peer, port_),
  };
  Peer_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Peer_descriptor_,
      Peer::default_instance_,
      Peer_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Peer, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Peer, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Peer));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_download_5finfo_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    DownloadInfo_descriptor_, &DownloadInfo::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Peer_descriptor_, &Peer::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_download_5finfo_2eproto() {
  delete DownloadInfo::default_instance_;
  delete DownloadInfo_reflection_;
  delete Peer::default_instance_;
  delete Peer_reflection_;
}

void protobuf_AddDesc_download_5finfo_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\023download_info.proto\022\010download\"I\n\014Downl"
    "oadInfo\022\026\n\016file_byte_size\030\002 \002(\003\022!\n\tpeer_"
    "info\030\001 \003(\0132\016.download.Peer\" \n\004Peer\022\n\n\002ip"
    "\030\001 \002(\t\022\014\n\004port\030\002 \002(\005", 140);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "download_info.proto", &protobuf_RegisterTypes);
  DownloadInfo::default_instance_ = new DownloadInfo();
  Peer::default_instance_ = new Peer();
  DownloadInfo::default_instance_->InitAsDefaultInstance();
  Peer::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_download_5finfo_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_download_5finfo_2eproto {
  StaticDescriptorInitializer_download_5finfo_2eproto() {
    protobuf_AddDesc_download_5finfo_2eproto();
  }
} static_descriptor_initializer_download_5finfo_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int DownloadInfo::kFileByteSizeFieldNumber;
const int DownloadInfo::kPeerInfoFieldNumber;
#endif  // !_MSC_VER

DownloadInfo::DownloadInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:download.DownloadInfo)
}

void DownloadInfo::InitAsDefaultInstance() {
}

DownloadInfo::DownloadInfo(const DownloadInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:download.DownloadInfo)
}

void DownloadInfo::SharedCtor() {
  _cached_size_ = 0;
  file_byte_size_ = GOOGLE_LONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

DownloadInfo::~DownloadInfo() {
  // @@protoc_insertion_point(destructor:download.DownloadInfo)
  SharedDtor();
}

void DownloadInfo::SharedDtor() {
  if (this != default_instance_) {
  }
}

void DownloadInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* DownloadInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return DownloadInfo_descriptor_;
}

const DownloadInfo& DownloadInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_download_5finfo_2eproto();
  return *default_instance_;
}

DownloadInfo* DownloadInfo::default_instance_ = NULL;

DownloadInfo* DownloadInfo::New() const {
  return new DownloadInfo;
}

void DownloadInfo::Clear() {
  file_byte_size_ = GOOGLE_LONGLONG(0);
  peer_info_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool DownloadInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:download.DownloadInfo)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .download.Peer peer_info = 1;
      case 1: {
        if (tag == 10) {
         parse_peer_info:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_peer_info()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_peer_info;
        if (input->ExpectTag(16)) goto parse_file_byte_size;
        break;
      }

      // required int64 file_byte_size = 2;
      case 2: {
        if (tag == 16) {
         parse_file_byte_size:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &file_byte_size_)));
          set_has_file_byte_size();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:download.DownloadInfo)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:download.DownloadInfo)
  return false;
#undef DO_
}

void DownloadInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:download.DownloadInfo)
  // repeated .download.Peer peer_info = 1;
  for (int i = 0; i < this->peer_info_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->peer_info(i), output);
  }

  // required int64 file_byte_size = 2;
  if (has_file_byte_size()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(2, this->file_byte_size(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:download.DownloadInfo)
}

::google::protobuf::uint8* DownloadInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:download.DownloadInfo)
  // repeated .download.Peer peer_info = 1;
  for (int i = 0; i < this->peer_info_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->peer_info(i), target);
  }

  // required int64 file_byte_size = 2;
  if (has_file_byte_size()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(2, this->file_byte_size(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:download.DownloadInfo)
  return target;
}

int DownloadInfo::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int64 file_byte_size = 2;
    if (has_file_byte_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->file_byte_size());
    }

  }
  // repeated .download.Peer peer_info = 1;
  total_size += 1 * this->peer_info_size();
  for (int i = 0; i < this->peer_info_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->peer_info(i));
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void DownloadInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const DownloadInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const DownloadInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void DownloadInfo::MergeFrom(const DownloadInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  peer_info_.MergeFrom(from.peer_info_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_file_byte_size()) {
      set_file_byte_size(from.file_byte_size());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void DownloadInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void DownloadInfo::CopyFrom(const DownloadInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DownloadInfo::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->peer_info())) return false;
  return true;
}

void DownloadInfo::Swap(DownloadInfo* other) {
  if (other != this) {
    std::swap(file_byte_size_, other->file_byte_size_);
    peer_info_.Swap(&other->peer_info_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata DownloadInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = DownloadInfo_descriptor_;
  metadata.reflection = DownloadInfo_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Peer::kIpFieldNumber;
const int Peer::kPortFieldNumber;
#endif  // !_MSC_VER

Peer::Peer()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:download.Peer)
}

void Peer::InitAsDefaultInstance() {
}

Peer::Peer(const Peer& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:download.Peer)
}

void Peer::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  ip_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  port_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Peer::~Peer() {
  // @@protoc_insertion_point(destructor:download.Peer)
  SharedDtor();
}

void Peer::SharedDtor() {
  if (ip_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete ip_;
  }
  if (this != default_instance_) {
  }
}

void Peer::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Peer::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Peer_descriptor_;
}

const Peer& Peer::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_download_5finfo_2eproto();
  return *default_instance_;
}

Peer* Peer::default_instance_ = NULL;

Peer* Peer::New() const {
  return new Peer;
}

void Peer::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    if (has_ip()) {
      if (ip_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        ip_->clear();
      }
    }
    port_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Peer::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:download.Peer)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string ip = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_ip()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->ip().data(), this->ip().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "ip");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_port;
        break;
      }

      // required int32 port = 2;
      case 2: {
        if (tag == 16) {
         parse_port:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &port_)));
          set_has_port();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:download.Peer)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:download.Peer)
  return false;
#undef DO_
}

void Peer::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:download.Peer)
  // required string ip = 1;
  if (has_ip()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->ip().data(), this->ip().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "ip");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->ip(), output);
  }

  // required int32 port = 2;
  if (has_port()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->port(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:download.Peer)
}

::google::protobuf::uint8* Peer::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:download.Peer)
  // required string ip = 1;
  if (has_ip()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->ip().data(), this->ip().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "ip");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->ip(), target);
  }

  // required int32 port = 2;
  if (has_port()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->port(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:download.Peer)
  return target;
}

int Peer::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string ip = 1;
    if (has_ip()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->ip());
    }

    // required int32 port = 2;
    if (has_port()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->port());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Peer::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Peer* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Peer*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Peer::MergeFrom(const Peer& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_ip()) {
      set_ip(from.ip());
    }
    if (from.has_port()) {
      set_port(from.port());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Peer::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Peer::CopyFrom(const Peer& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Peer::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void Peer::Swap(Peer* other) {
  if (other != this) {
    std::swap(ip_, other->ip_);
    std::swap(port_, other->port_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Peer::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Peer_descriptor_;
  metadata.reflection = Peer_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace download

// @@protoc_insertion_point(global_scope)
