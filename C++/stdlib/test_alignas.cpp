// Copyright 2019 All Rights Reserved.
// some code port from facebook Folly

#include <iostream>
#include <vector>
#include <assert.h>

struct Foo {
  alignas(0x40) float array[1];
  Foo() {
    std::cout << "ctor " << array << "\n";
  }
};

template<typename T>
class Poo {
public:
    template<typename U, std::enable_if_t<!std::is_same<T, U>::value, int> = 0>
    size_t operator=(Poo<U>& value) {
        _value = value._value;
        return 0;
    }
    int _value;
};

template<typename T>
struct lift_void_to_char {
    using type = T;
};
template<>
struct lift_void_to_char<void> {
    using type = char;
};
inline void* aligned_malloc(size_t size, size_t align) {
  // use posix_memalign, but mimic the behaviour of memalign
  void* ptr = nullptr;
  int rc = posix_memalign(&ptr, align, size);
  return rc == 0 ? (errno = 0, ptr) : (errno = rc, nullptr);
}

inline void aligned_free(void* aligned_ptr) {
  free(aligned_ptr);
}

template<uint32_t aligned_size>
class DefaultAlign {
 private:
  using Self = DefaultAlign;
  std::size_t align_;

 public:
  explicit DefaultAlign() noexcept : align_(aligned_size) {
    assert(!(align_ < sizeof(void*)) && bool("bad align: too small"));
    assert(!(align_ & (align_ - 1)) && bool("bad align: not power-of-two"));
  }
  std::size_t operator()(std::size_t align) const noexcept {
    return align_ < align ? align : align_;
  }

  friend bool operator==(Self const& a, Self const& b) noexcept {
    return a.align_ == b.align_;
  }
  friend bool operator!=(Self const& a, Self const& b) noexcept {
    return a.align_ != b.align_;
  }
};

template<uint32_t asize>
class UintWrapper {
public:
    constexpr static uint32_t i_value = asize;
};

// template <typename T, typename Align = DefaultAlign<64>>
template <typename T, typename Align = UintWrapper<64>>
class AlignedSysAllocator {
 private:
  using Self = AlignedSysAllocator<T, Align>;
  template <typename, typename>
  friend class AlignedSysAllocator;
  // constexpr Align const& align() const {
  //   return *this;
  // }

 public:
  static_assert(std::is_nothrow_copy_constructible<Align>::value, "");
  // static_assert(is_nothrow_invocable_r_v<std::size_t, Align, std::size_t>, "");

  using value_type = T;

  using propagate_on_container_copy_assignment = std::true_type;
  using propagate_on_container_move_assignment = std::true_type;
  using propagate_on_container_swap = std::true_type;

  // using Align::Align;

  // TODO: remove this ctor, which is is no longer required as of under gcc7
  // template <
  //     typename S = Align,
  //     std::enable_if_t<std::is_default_constructible<S>::value, int> = 0>
  // constexpr AlignedSysAllocator() noexcept(noexcept(Align())) : Align() {}

  constexpr AlignedSysAllocator() = default;
  constexpr AlignedSysAllocator(AlignedSysAllocator const&) = default;

  // template <typename U, std::enable_if_t<!std::is_same<U, T>::value, int> = 0>
  // constexpr AlignedSysAllocator(
  //     AlignedSysAllocator<U, Align> const& other) noexcept
  //     : Align(other.align()) {}

  template <typename U, std::enable_if_t<!std::is_same<U, T>::value, int> = 0>
  constexpr AlignedSysAllocator(
      AlignedSysAllocator<U, Align> const& other) noexcept {}
      

  T* allocate(size_t count) {
    using lifted = typename lift_void_to_char<T>::type;
    // auto const a = align()(alignof(lifted));
    auto const a = Align::i_value;
    auto const p = aligned_malloc(sizeof(lifted) * count, a);
    if (!p) {
      if ((errno != ENOMEM)) {
        std::terminate();
      }
      throw std::bad_alloc();
    }
    return static_cast<T*>(p);
  }
  void deallocate(T* p, size_t /* count */) {
    aligned_free(p);
  }
};

// template<typename T, uint32_t aligned_size = 64>
// class AlignedSysAllocator {
// private:
//   using Self = AlignedSysAllocator<T, aligned_size>;
// public:
//   using value_type = T;
//   // template <typename, typename>
//   // friend class AlignedSysAllocator;
//   using propagate_on_container_copy_assignment = std::true_type;
//   using propagate_on_container_move_assignment = std::true_type;
//   using propagate_on_container_swap = std::true_type;
// 
//   constexpr AlignedSysAllocator() noexcept {} 
//   constexpr AlignedSysAllocator(AlignedSysAllocator const&) = default;
// 
//   // template <typename U, std::enable_if_t<!std::is_same<U, T>::value, int> = 0>
//   // constexpr AlignedSysAllocator(
//   //     AlignedSysAllocator<U, aligned_size> const& other) noexcept
//   //     {}
//   const size_t align(const uint32_t& obj_align) {
//       return std::max(aligned_size, obj_align);
//   }
// 
//   T* allocate(size_t count) {
//     using lifted = typename lift_void_to_char<T>::type;
//     auto const a = align(alignof(lifted));
//     auto const p = aligned_malloc(sizeof(lifted) * count, a);
//     if (!p) {
//       if ((errno != ENOMEM)) {
//         std::terminate();
//       }
//       throw std::bad_alloc();
//     }
//     return static_cast<T*>(p);
//   }
//   void deallocate(T* p, size_t) {
//     aligned_free(p);
//   }
// };

int main() {
  Foo f[3];
  printf("%u\n", alignof(f[0]));
  printf("%u\n", alignof(f[1]));
  printf("%u\n", alignof(f[2]));
  std::vector<Foo> vec(2);
  printf("%u\t%p\n", alignof(vec[0]), &(vec[0]));
  printf("%u\t%p\n", alignof(vec[1]), &(vec[1]));
  Poo<int> pi;
  Poo<int> pd;
  pd._value = 1002;
  pi = pd;
  printf("%d\t%d\n", pd._value, pi._value);
  printf("%d\n", sizeof(lift_void_to_char<void>::type));
  std::vector<Foo, AlignedSysAllocator<Foo>> data(3);
  // AlignedSysAllocator<Foo> alloc;
  // Foo* fa = alloc.allocate(3);
  // printf("%u\t%p\n", alignof(*fa), fa);
  // printf("%u\t%p\n", alignof(fa[1]), fa + 1);
  printf("%u\t%p\n", alignof(data[0]), &(data[0]));
  printf("%u\t%p\n", alignof(data[1]), &(data[1]));
  return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
