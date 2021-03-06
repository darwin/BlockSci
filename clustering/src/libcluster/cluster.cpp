//
//  cluster.cpp
//  blocksci
//
//  Created by Harry Kalodner on 7/6/17.
//
//

#include "cluster.hpp"

#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/algorithm/copy.hpp>

#include "cluster_manager.hpp"

boost::iterator_range<const blocksci::Address *> Cluster::getAddresses() const {
    return manager.getClusterAddresses(clusterNum);
}

uint32_t Cluster::getSize() const {
    return manager.getClusterSize(clusterNum);
}

std::vector<TaggedAddress> Cluster::taggedAddresses(const std::unordered_map<blocksci::Address, std::string> &tags) const {
    std::vector<TaggedAddress> tagged;
    for (auto &address : getAddresses()) {
        auto it = tags.find(address);
        if (it != tags.end()) {
            tagged.emplace_back(it->first, it->second);
        }
    }
    return tagged;
}

uint32_t Cluster::getAddressCount(blocksci::AddressType::Enum type) const {
    uint32_t count = 0;
    for (auto &address : getAddresses()) {
        if (address.type == type) {
            ++count;
        }
    }
    return count;
}
