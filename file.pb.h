// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: file.proto

#ifndef PROTOBUF_file_2eproto__INCLUDED
#define PROTOBUF_file_2eproto__INCLUDED

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

namespace file {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_file_2eproto();
void protobuf_AssignDesc_file_2eproto();
void protobuf_ShutdownFile_file_2eproto();

class Files;
class File;

// ===================================================================

class Files : public ::google::protobuf::Message {
 public:
  Files();
  virtual ~Files();

  Files(const Files& from);

  inline Files& operator=(const Files& from) {
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
  static const Files& default_instance();

  void Swap(Files* other);

  // implements Message ----------------------------------------------

  Files* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Files& from);
  void MergeFrom(const Files& from);
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

  // repeated .file.File files = 1;
  inline int files_size() const;
  inline void clear_files();
  static const int kFilesFieldNumber = 1;
  inline const ::file::File& files(int index) const;
  inline ::file::File* mutable_files(int index);
  inline ::file::File* add_files();
  inline const ::google::protobuf::RepeatedPtrField< ::file::File >&
      files() const;
  inline ::google::protobuf::RepeatedPtrField< ::file::File >*
      mutable_files();

  // @@protoc_insertion_point(class_scope:file.Files)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::file::File > files_;
  friend void  protobuf_AddDesc_file_2eproto();
  friend void protobuf_AssignDesc_file_2eproto();
  friend void protobuf_ShutdownFile_file_2eproto();

  void InitAsDefaultInstance();
  static Files* default_instance_;
};
// -------------------------------------------------------------------

class File : public ::google::protobuf::Message {
 public:
  File();
  virtual ~File();

  File(const File& from);

  inline File& operator=(const File& from) {
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
  static const File& default_instance();

  void Swap(File* other);

  // implements Message ----------------------------------------------

  File* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const File& from);
  void MergeFrom(const File& from);
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

  // required string file_name = 1;
  inline bool has_file_name() const;
  inline void clear_file_name();
  static const int kFileNameFieldNumber = 1;
  inline const ::std::string& file_name() const;
  inline void set_file_name(const ::std::string& value);
  inline void set_file_name(const char* value);
  inline void set_file_name(const char* value, size_t size);
  inline ::std::string* mutable_file_name();
  inline ::std::string* release_file_name();
  inline void set_allocated_file_name(::std::string* file_name);

  // @@protoc_insertion_point(class_scope:file.File)
 private:
  inline void set_has_file_name();
  inline void clear_has_file_name();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* file_name_;
  friend void  protobuf_AddDesc_file_2eproto();
  friend void protobuf_AssignDesc_file_2eproto();
  friend void protobuf_ShutdownFile_file_2eproto();

  void InitAsDefaultInstance();
  static File* default_instance_;
};
// ===================================================================


// ===================================================================

// Files

// repeated .file.File files = 1;
inline int Files::files_size() const {
  return files_.size();
}
inline void Files::clear_files() {
  files_.Clear();
}
inline const ::file::File& Files::files(int index) const {
  // @@protoc_insertion_point(field_get:file.Files.files)
  return files_.Get(index);
}
inline ::file::File* Files::mutable_files(int index) {
  // @@protoc_insertion_point(field_mutable:file.Files.files)
  return files_.Mutable(index);
}
inline ::file::File* Files::add_files() {
  // @@protoc_insertion_point(field_add:file.Files.files)
  return files_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::file::File >&
Files::files() const {
  // @@protoc_insertion_point(field_list:file.Files.files)
  return files_;
}
inline ::google::protobuf::RepeatedPtrField< ::file::File >*
Files::mutable_files() {
  // @@protoc_insertion_point(field_mutable_list:file.Files.files)
  return &files_;
}

// -------------------------------------------------------------------

// File

// required string file_name = 1;
inline bool File::has_file_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void File::set_has_file_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void File::clear_has_file_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void File::clear_file_name() {
  if (file_name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    file_name_->clear();
  }
  clear_has_file_name();
}
inline const ::std::string& File::file_name() const {
  // @@protoc_insertion_point(field_get:file.File.file_name)
  return *file_name_;
}
inline void File::set_file_name(const ::std::string& value) {
  set_has_file_name();
  if (file_name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    file_name_ = new ::std::string;
  }
  file_name_->assign(value);
  // @@protoc_insertion_point(field_set:file.File.file_name)
}
inline void File::set_file_name(const char* value) {
  set_has_file_name();
  if (file_name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    file_name_ = new ::std::string;
  }
  file_name_->assign(value);
  // @@protoc_insertion_point(field_set_char:file.File.file_name)
}
inline void File::set_file_name(const char* value, size_t size) {
  set_has_file_name();
  if (file_name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    file_name_ = new ::std::string;
  }
  file_name_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:file.File.file_name)
}
inline ::std::string* File::mutable_file_name() {
  set_has_file_name();
  if (file_name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    file_name_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:file.File.file_name)
  return file_name_;
}
inline ::std::string* File::release_file_name() {
  clear_has_file_name();
  if (file_name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = file_name_;
    file_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void File::set_allocated_file_name(::std::string* file_name) {
  if (file_name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete file_name_;
  }
  if (file_name) {
    set_has_file_name();
    file_name_ = file_name;
  } else {
    clear_has_file_name();
    file_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:file.File.file_name)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace file

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_file_2eproto__INCLUDED
