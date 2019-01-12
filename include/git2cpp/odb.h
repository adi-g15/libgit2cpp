#pragma once

#include "odb_object.h"

#include <git2/oid.h>

struct git_odb;

namespace git
{
    struct Odb
    {
        explicit Odb(git_repository * repo);
        ~Odb();

        OdbObject read(git_oid const & oid) const;
        git_oid write(const void * data, size_t len, git_otype type);

        Odb(Odb const &) = delete;
        Odb & operator=(Odb const &) = delete;

        Odb(Odb && other) noexcept;

    private:
        git_odb * odb_;
    };
}
