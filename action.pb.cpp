// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: action.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "action.pb.h"

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

namespace action {

namespace {

const ::google::protobuf::Descriptor* Action_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Action_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_action_2eproto() {
  protobuf_AddDesc_action_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "action.proto");
  GOOGLE_CHECK(file != NULL);
  Action_descriptor_ = file->message_type(0);
  static const int Action_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Action, action_),
  };
  Action_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Action_descriptor_,
      Action::default_instance_,
      Action_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Action, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Action, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Action));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_action_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Action_descriptor_, &Action::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_action_2eproto() {
  delete Action::default_instance_;
  delete Action_reflection_;
}

void protobuf_AddDesc_action_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\014action.proto\022\006action\"\030\n\006Action\022\016\n\006acti"
    "on\030\001 \002(\t", 48);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "action.proto", &protobuf_RegisterTypes);
  Action::default_instance_ = new Action();
  Action::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_action_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_action_2eproto {
  StaticDescriptorInitializer_action_2eproto() {
    protobuf_AddDesc_action_2eproto();
  }
} static_descriptor_initializer_action_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Action::kActionFieldNumber;
#endif  // !_MSC_VER

Action::Action()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:action.Action)
}

void Action::InitAsDefaultInstance() {
}

Action::Action(const Action& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:action.Action)
}

void Action::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  action_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Action::~Action() {
  // @@protoc_insertion_point(destructor:action.Action)
  SharedDtor();
}

void Action::SharedDtor() {
  if (action_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete action_;
  }
  if (this != default_instance_) {
  }
}

void Action::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Action::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Action_descriptor_;
}

const Action& Action::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_action_2eproto();
  return *default_instance_;
}

Action* Action::default_instance_ = NULL;

Action* Action::New() const {
  return new Action;
}

void Action::Clear() {
  if (has_action()) {
    if (action_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
      action_->clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Action::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:action.Action)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string action = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_action()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->action().data(), this->action().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "action");
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
  // @@protoc_insertion_point(parse_success:action.Action)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:action.Action)
  return false;
#undef DO_
}

void Action::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:action.Action)
  // required string action = 1;
  if (has_action()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->action().data(), this->action().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "action");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->action(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:action.Action)
}

::google::protobuf::uint8* Action::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:action.Action)
  // required string action = 1;
  if (has_action()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->action().data(), this->action().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "action");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->action(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:action.Action)
  return target;
}

int Action::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string action = 1;
    if (has_action()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->action());
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

void Action::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Action* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Action*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Action::MergeFrom(const Action& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_action()) {
      set_action(from.action());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Action::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Action::CopyFrom(const Action& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Action::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void Action::Swap(Action* other) {
  if (other != this) {
    std::swap(action_, other->action_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Action::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Action_descriptor_;
  metadata.reflection = Action_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace action

// @@protoc_insertion_point(global_scope)