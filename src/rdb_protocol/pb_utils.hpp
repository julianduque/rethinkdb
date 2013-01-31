#ifndef RDB_PROTOCOL_PB_UTILS_HPP_
#define RDB_PROTOCOL_PB_UTILS_HPP_

#include "rdb_protocol/ql2.pb.h"

namespace ql {
namespace pb {

Datum *set_datum(Term2 *d);
Term2 *set_func(Term2 *f, int varnum);
Term2 *set_func(Term2 *f, int varnum1, int varnum2);
void set_var(Term2 *v, int varnum);

void set_null(Term2 *t);
void set_int(Term2 *t, int num);
void set_str(Term2 *t, const std::string &s);

void set(Term2 *out, Term2_TermType type, std::vector<Term2 *> *args_out, int num_args);

#define N0(PB)                                  \
    arg->set_type(Term2_TermType_##PB);
#define N1(PB, ARG1) {                          \
        arg->set_type(Term2_TermType_##PB);     \
        Term2 *__arg1 = arg->add_args();        \
        Term2 *arg = __arg1; ARG1;              \
    }
#define N2(PB, ARG1, ARG2) {                    \
        arg->set_type(Term2_TermType_##PB);     \
        Term2 *__arg1 = arg->add_args();        \
        Term2 *__arg2 = arg->add_args();        \
        Term2 *arg = __arg1; ARG1;              \
        arg = __arg2; ARG2;                     \
    }
#define N3(PB, ARG1, ARG2, ARG3) {              \
        arg->set_type(Term2_TermType_##PB);     \
        Term2 *__arg1 = arg->add_args();        \
        Term2 *__arg2 = arg->add_args();        \
        Term2 *__arg3 = arg->add_args();        \
        Term2 *arg = __arg1; ARG1;              \
        arg = __arg2; ARG2;                     \
        arg = __arg3; ARG3;                     \
    }
#define N4(PB, ARG1, ARG2, ARG3, ARG4) {        \
        arg->set_type(Term2_TermType_##PB);     \
        Term2 *__arg1 = arg->add_args();        \
        Term2 *__arg2 = arg->add_args();        \
        Term2 *__arg3 = arg->add_args();        \
        Term2 *__arg4 = arg->add_args();        \
        Term2 *arg = __arg1; ARG1;              \
        arg = __arg2; ARG2;                     \
        arg = __arg3; ARG3;                     \
        arg = __arg4; ARG4;                     \
    }

#define NVAR(varnum) pb::set_var(arg, varnum)
// TODO: no need for this, just construct a temporary object.
#define NDATUM(env, val) \
    env->add_ptr(new datum_t(val))->write_to_protobuf(pb::set_datum(arg))

#define OPT1(PB, STR1, ARG1) {                          \
        arg->set_type(Term2_TermType_##PB);             \
        Term2_AssocPair *__ap1 = arg->add_optargs();    \
        __ap1->set_key(STR1);                           \
        arg = __ap1->mutable_val(); ARG1;               \
    }
#define OPT2(PB, STR1, ARG1, STR2, ARG2) {              \
        arg->set_type(Term2_TermType_##PB);             \
        Term2_AssocPair *__ap1 = arg->add_optargs();    \
        __ap1->set_key(STR1);                           \
        Term2_AssocPair *__ap2 = arg->add_optargs();    \
        __ap2->set_key(STR2);                           \
        arg = __ap1->mutable_val(); ARG1;               \
        arg = __ap2->mutable_val(); ARG2;               \
    }

template<class T>
T *reset(T *t) { *t = T(); return t; }

// To debug: term->DebugString()

} // namespace pb
} // namespace ql

#endif // RDB_PROTOCOL_PB_UTILS_HPP_
