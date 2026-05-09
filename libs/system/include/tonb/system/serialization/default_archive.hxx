//
// Created by amir on 8/16/25.
//
#pragma once
#ifndef TONB_SYSTEM_DEFAULT_ARCHIVE_HXX
#define TONB_SYSTEM_DEFAULT_ARCHIVE_HXX
/*------------------------------------------------------------------------------
  File: default_archive.hpp
  Purpose:
    Backend selector for serialization archives. This header exposes a stable
    pair of type aliases:

        tonb::system::serialization::oarchive   // output serializer
        tonb::system::serialization::iarchive   // input  serializer

    The actual backend is chosen at build time:

      - TNB_WITH_CEREAL defined  → cereal backend (header-only)
      - otherwise                → Boost.Serialization backend

  Why:
    Lets model code write a single `serialize(Archive& ar)` that is backend
    agnostic. Swapping the backend is a CMake switch, not a code rewrite.

  Build integration:
    - CMake should set the compile definition on the library target that
      includes this header:
        target_compile_definitions(tnbsystem PUBLIC TNB_WITH_CEREAL)
    - And pull the right dependency:
        find_package(cereal CONFIG REQUIRED)      # if using cereal
        # or
        find_package(Boost CONFIG REQUIRED COMPONENTS serialization)
        target_link_libraries(tnbsystem PUBLIC Boost::serialization)

  Usage:
    #include "tnb/ser/default_archive.hpp"

    tonb::system::serialization::oarchive oa(os);   // wraps std::ostream
    tonb::system::serialization::iarchive ia(is);   // wraps std::istream
    obj.serialize(oa);           // same code for both backends
    obj.serialize(ia);

  Notes:
    - Do not include both adapters in the same TU; this header chooses one.
    - Keep the compile definition consistent across all TUs of the binary
      (avoid ODR mismatches). Make it a PUBLIC definition on your library.
    - Archives are not thread-safe; use separate instances per thread.
    - Exception surface: both backends may throw on I/O/format errors; catch at
      call sites or provide no-throw wrappers that return std::error_code.

------------------------------------------------------------------------------*/

// Exactly one backend should be active.
// (It’s fine that only TNB_WITH_CEREAL is user-controlled; "boost" is default.)

#if defined(TNB_WITH_CEREAL)
  #include "cereal_archive.hpp"
  namespace tonb::system::serialization {
    using oarchive = cereal_oarchive;
    using iarchive = cereal_iarchive;
    inline constexpr const char* backend_name = "cereal";
  }
#else
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
namespace tonb::system::serialization {
    //using oarchive = boost::archive::binary_oarchive;
    //using iarchive = boost::archive::binary_iarchive;
    inline constexpr auto backend_name = "boost";

    struct oarchive {
      boost::archive::binary_oarchive ar;
      explicit oarchive(std::ostream& os) : ar(os) {}
      template<class... Ts>
      void operator()(Ts&... xs) { (ar & ... & xs); }  // fold expression
    };

    struct iarchive {
      boost::archive::binary_iarchive ar;
      explicit iarchive(std::istream& is) : ar(is) {}
      template<class... Ts>
      void operator()(Ts&... xs) { (ar & ... & xs); }  // works for loading too
    };
  }
#endif

// Build-time sanity checks (fail fast if adapters forgot to define types)
static_assert(std::is_class_v<tonb::system::serialization::oarchive>, "oarchive alias not defined");
static_assert(std::is_class_v<tonb::system::serialization::iarchive>, "iarchive alias not defined");
#endif //TONB_GLOBAL_DEFAULT_ARCHIVE_HXX