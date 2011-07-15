
#ifndef __ARCH_ADDRESS_HPP__
#define __ARCH_ADDRESS_HPP__

#include <boost/serialization/access.hpp>
#include <boost/serialization/binary_object.hpp>
#include <netinet/in.h>
#include "utils.hpp" // (for UNUSED macro)

/* ip_address_t represents an IPv4 address. */
struct ip_address_t {
    ip_address_t() { }
    ip_address_t(const char *);   // Address with hostname or IP
    ip_address_t(uint32_t);
    static ip_address_t us();

    bool operator==(const ip_address_t &x) const;   // Compare addresses
    bool operator!=(const ip_address_t &x) const;

public:
    uint32_t ip_as_uint32();

public:
    struct in_addr addr;

private:
    friend class boost::serialization::access;
    template<class Archive> void serialize(Archive & ar, UNUSED const unsigned int version) {
        // Not really platform independent...
        boost::serialization::binary_object bin_addr(&addr, sizeof(in_addr));
        ar & bin_addr;
    }
};

#endif /* __ARCH_ADDRESS_HPP__ */
