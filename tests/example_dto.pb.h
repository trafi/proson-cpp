// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: example_dto.proto

#ifndef PROTOBUF_example_5fdto_2eproto__INCLUDED
#define PROTOBUF_example_5fdto_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3002000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3002000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace example_dto {
class Position;
class PositionDefaultTypeInternal;
extern PositionDefaultTypeInternal _Position_default_instance_;
class Servo;
class ServoDefaultTypeInternal;
extern ServoDefaultTypeInternal _Servo_default_instance_;
class Target;
class TargetDefaultTypeInternal;
extern TargetDefaultTypeInternal _Target_default_instance_;
}  // namespace example_dto

namespace example_dto {

namespace protobuf_example_5fdto_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_example_5fdto_2eproto

enum Air {
  Hot = 5,
  Cold = 0
};
bool Air_IsValid(int value);
const Air Air_MIN = Cold;
const Air Air_MAX = Hot;
const int Air_ARRAYSIZE = Air_MAX + 1;

const ::google::protobuf::EnumDescriptor* Air_descriptor();
inline const ::std::string& Air_Name(Air value) {
  return ::google::protobuf::internal::NameOfEnum(
    Air_descriptor(), value);
}
inline bool Air_Parse(
    const ::std::string& name, Air* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Air>(
    Air_descriptor(), name, value);
}
// ===================================================================

class Position : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:example_dto.Position) */ {
 public:
  Position();
  virtual ~Position();

  Position(const Position& from);

  inline Position& operator=(const Position& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Position& default_instance();

  static inline const Position* internal_default_instance() {
    return reinterpret_cast<const Position*>(
               &_Position_default_instance_);
  }

  void Swap(Position* other);

  // implements Message ----------------------------------------------

  inline Position* New() const PROTOBUF_FINAL { return New(NULL); }

  Position* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Position& from);
  void MergeFrom(const Position& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output)
      const PROTOBUF_FINAL {
    return InternalSerializeWithCachedSizesToArray(
        ::google::protobuf::io::CodedOutputStream::IsDefaultSerializationDeterministic(), output);
  }
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Position* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required double x = 1;
  bool has_x() const;
  void clear_x();
  static const int kXFieldNumber = 1;
  double x() const;
  void set_x(double value);

  // required double y = 2;
  bool has_y() const;
  void clear_y();
  static const int kYFieldNumber = 2;
  double y() const;
  void set_y(double value);

  // required double z = 3;
  bool has_z() const;
  void clear_z();
  static const int kZFieldNumber = 3;
  double z() const;
  void set_z(double value);

  // @@protoc_insertion_point(class_scope:example_dto.Position)
 private:
  void set_has_x();
  void clear_has_x();
  void set_has_y();
  void clear_has_y();
  void set_has_z();
  void clear_has_z();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  double x_;
  double y_;
  double z_;
  friend struct  protobuf_example_5fdto_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Target : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:example_dto.Target) */ {
 public:
  Target();
  virtual ~Target();

  Target(const Target& from);

  inline Target& operator=(const Target& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Target& default_instance();

  static inline const Target* internal_default_instance() {
    return reinterpret_cast<const Target*>(
               &_Target_default_instance_);
  }

  void Swap(Target* other);

  // implements Message ----------------------------------------------

  inline Target* New() const PROTOBUF_FINAL { return New(NULL); }

  Target* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Target& from);
  void MergeFrom(const Target& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output)
      const PROTOBUF_FINAL {
    return InternalSerializeWithCachedSizesToArray(
        ::google::protobuf::io::CodedOutputStream::IsDefaultSerializationDeterministic(), output);
  }
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Target* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .example_dto.Position pos = 2;
  bool has_pos() const;
  void clear_pos();
  static const int kPosFieldNumber = 2;
  const ::example_dto::Position& pos() const;
  ::example_dto::Position* mutable_pos();
  ::example_dto::Position* release_pos();
  void set_allocated_pos(::example_dto::Position* pos);

  // required sint64 updated_at = 1;
  bool has_updated_at() const;
  void clear_updated_at();
  static const int kUpdatedAtFieldNumber = 1;
  ::google::protobuf::int64 updated_at() const;
  void set_updated_at(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:example_dto.Target)
 private:
  void set_has_updated_at();
  void clear_has_updated_at();
  void set_has_pos();
  void clear_has_pos();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::example_dto::Position* pos_;
  ::google::protobuf::int64 updated_at_;
  friend struct  protobuf_example_5fdto_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Servo : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:example_dto.Servo) */ {
 public:
  Servo();
  virtual ~Servo();

  Servo(const Servo& from);

  inline Servo& operator=(const Servo& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Servo& default_instance();

  static inline const Servo* internal_default_instance() {
    return reinterpret_cast<const Servo*>(
               &_Servo_default_instance_);
  }

  void Swap(Servo* other);

  // implements Message ----------------------------------------------

  inline Servo* New() const PROTOBUF_FINAL { return New(NULL); }

  Servo* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Servo& from);
  void MergeFrom(const Servo& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output)
      const PROTOBUF_FINAL {
    return InternalSerializeWithCachedSizesToArray(
        ::google::protobuf::io::CodedOutputStream::IsDefaultSerializationDeterministic(), output);
  }
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Servo* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .example_dto.Target targets = 1;
  int targets_size() const;
  void clear_targets();
  static const int kTargetsFieldNumber = 1;
  const ::example_dto::Target& targets(int index) const;
  ::example_dto::Target* mutable_targets(int index);
  ::example_dto::Target* add_targets();
  ::google::protobuf::RepeatedPtrField< ::example_dto::Target >*
      mutable_targets();
  const ::google::protobuf::RepeatedPtrField< ::example_dto::Target >&
      targets() const;

  // optional float rpm = 2;
  bool has_rpm() const;
  void clear_rpm();
  static const int kRpmFieldNumber = 2;
  float rpm() const;
  void set_rpm(float value);

  // optional .example_dto.Air air = 3;
  bool has_air() const;
  void clear_air();
  static const int kAirFieldNumber = 3;
  ::example_dto::Air air() const;
  void set_air(::example_dto::Air value);

  // @@protoc_insertion_point(class_scope:example_dto.Servo)
 private:
  void set_has_rpm();
  void clear_has_rpm();
  void set_has_air();
  void clear_has_air();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::example_dto::Target > targets_;
  float rpm_;
  int air_;
  friend struct  protobuf_example_5fdto_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Position

// required double x = 1;
inline bool Position::has_x() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Position::set_has_x() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Position::clear_has_x() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Position::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline double Position::x() const {
  // @@protoc_insertion_point(field_get:example_dto.Position.x)
  return x_;
}
inline void Position::set_x(double value) {
  set_has_x();
  x_ = value;
  // @@protoc_insertion_point(field_set:example_dto.Position.x)
}

// required double y = 2;
inline bool Position::has_y() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Position::set_has_y() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Position::clear_has_y() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Position::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline double Position::y() const {
  // @@protoc_insertion_point(field_get:example_dto.Position.y)
  return y_;
}
inline void Position::set_y(double value) {
  set_has_y();
  y_ = value;
  // @@protoc_insertion_point(field_set:example_dto.Position.y)
}

// required double z = 3;
inline bool Position::has_z() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Position::set_has_z() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Position::clear_has_z() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Position::clear_z() {
  z_ = 0;
  clear_has_z();
}
inline double Position::z() const {
  // @@protoc_insertion_point(field_get:example_dto.Position.z)
  return z_;
}
inline void Position::set_z(double value) {
  set_has_z();
  z_ = value;
  // @@protoc_insertion_point(field_set:example_dto.Position.z)
}

// -------------------------------------------------------------------

// Target

// required sint64 updated_at = 1;
inline bool Target::has_updated_at() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Target::set_has_updated_at() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Target::clear_has_updated_at() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Target::clear_updated_at() {
  updated_at_ = GOOGLE_LONGLONG(0);
  clear_has_updated_at();
}
inline ::google::protobuf::int64 Target::updated_at() const {
  // @@protoc_insertion_point(field_get:example_dto.Target.updated_at)
  return updated_at_;
}
inline void Target::set_updated_at(::google::protobuf::int64 value) {
  set_has_updated_at();
  updated_at_ = value;
  // @@protoc_insertion_point(field_set:example_dto.Target.updated_at)
}

// required .example_dto.Position pos = 2;
inline bool Target::has_pos() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Target::set_has_pos() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Target::clear_has_pos() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Target::clear_pos() {
  if (pos_ != NULL) pos_->::example_dto::Position::Clear();
  clear_has_pos();
}
inline const ::example_dto::Position& Target::pos() const {
  // @@protoc_insertion_point(field_get:example_dto.Target.pos)
  return pos_ != NULL ? *pos_
                         : *::example_dto::Position::internal_default_instance();
}
inline ::example_dto::Position* Target::mutable_pos() {
  set_has_pos();
  if (pos_ == NULL) {
    pos_ = new ::example_dto::Position;
  }
  // @@protoc_insertion_point(field_mutable:example_dto.Target.pos)
  return pos_;
}
inline ::example_dto::Position* Target::release_pos() {
  // @@protoc_insertion_point(field_release:example_dto.Target.pos)
  clear_has_pos();
  ::example_dto::Position* temp = pos_;
  pos_ = NULL;
  return temp;
}
inline void Target::set_allocated_pos(::example_dto::Position* pos) {
  delete pos_;
  pos_ = pos;
  if (pos) {
    set_has_pos();
  } else {
    clear_has_pos();
  }
  // @@protoc_insertion_point(field_set_allocated:example_dto.Target.pos)
}

// -------------------------------------------------------------------

// Servo

// repeated .example_dto.Target targets = 1;
inline int Servo::targets_size() const {
  return targets_.size();
}
inline void Servo::clear_targets() {
  targets_.Clear();
}
inline const ::example_dto::Target& Servo::targets(int index) const {
  // @@protoc_insertion_point(field_get:example_dto.Servo.targets)
  return targets_.Get(index);
}
inline ::example_dto::Target* Servo::mutable_targets(int index) {
  // @@protoc_insertion_point(field_mutable:example_dto.Servo.targets)
  return targets_.Mutable(index);
}
inline ::example_dto::Target* Servo::add_targets() {
  // @@protoc_insertion_point(field_add:example_dto.Servo.targets)
  return targets_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::example_dto::Target >*
Servo::mutable_targets() {
  // @@protoc_insertion_point(field_mutable_list:example_dto.Servo.targets)
  return &targets_;
}
inline const ::google::protobuf::RepeatedPtrField< ::example_dto::Target >&
Servo::targets() const {
  // @@protoc_insertion_point(field_list:example_dto.Servo.targets)
  return targets_;
}

// optional float rpm = 2;
inline bool Servo::has_rpm() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Servo::set_has_rpm() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Servo::clear_has_rpm() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Servo::clear_rpm() {
  rpm_ = 0;
  clear_has_rpm();
}
inline float Servo::rpm() const {
  // @@protoc_insertion_point(field_get:example_dto.Servo.rpm)
  return rpm_;
}
inline void Servo::set_rpm(float value) {
  set_has_rpm();
  rpm_ = value;
  // @@protoc_insertion_point(field_set:example_dto.Servo.rpm)
}

// optional .example_dto.Air air = 3;
inline bool Servo::has_air() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Servo::set_has_air() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Servo::clear_has_air() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Servo::clear_air() {
  air_ = 5;
  clear_has_air();
}
inline ::example_dto::Air Servo::air() const {
  // @@protoc_insertion_point(field_get:example_dto.Servo.air)
  return static_cast< ::example_dto::Air >(air_);
}
inline void Servo::set_air(::example_dto::Air value) {
  assert(::example_dto::Air_IsValid(value));
  set_has_air();
  air_ = value;
  // @@protoc_insertion_point(field_set:example_dto.Servo.air)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace example_dto

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::example_dto::Air> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::example_dto::Air>() {
  return ::example_dto::Air_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_example_5fdto_2eproto__INCLUDED
