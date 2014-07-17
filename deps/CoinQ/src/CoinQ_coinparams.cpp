///////////////////////////////////////////////////////////////////////////////
//
// CoinQ_coinparams.cpp
//
// Copyright (c) 2012-2014 Eric Lombrozo
//
// All Rights Reserved.

#include "CoinQ_coinparams.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace CoinQ
{

NetworkSelector::NetworkSelector(const std::string& network_name)
{
    network_map_.insert(NetworkPair("bitcoin", getBitcoinParams()));
    network_map_.insert(NetworkPair("testnet3", getTestnet3Params()));
    network_map_.insert(NetworkPair("litecoin", getLitecoinParams()));
    network_map_.insert(NetworkPair("quarkcoin", getQuarkcoinParams()));

    if (!network_name.empty()) { select(network_name); }
}

vector<string> NetworkSelector::getNetworkNames() const
{
    vector<string> names;
    for (const auto& item: network_map_) { names.push_back(item.first); }
    return names;
}

const CoinParams& NetworkSelector::getCoinParams(const std::string& network_name) const
{
    string lower_network_name;

    if (network_name.empty())   { lower_network_name = selected_;    }
    else                        { lower_network_name = network_name; }

    if (lower_network_name.empty()) throw runtime_error("NetworkSelector::getCoinParams() - no network selected.");

    transform(lower_network_name.begin(), lower_network_name.end(), lower_network_name.begin(), ::tolower);

    const auto& it = network_map_.find(lower_network_name);
    if (it == network_map_.end())
    {
        stringstream err;
        err << "NetworkSelector::getCoinParams() - network \"" << lower_network_name << "\" not recognized.";
        throw runtime_error(err.str());
    }

    return it->second;
}

void NetworkSelector::select(const std::string& network_name)
{
    string lower_network_name(network_name);
    transform(lower_network_name.begin(), lower_network_name.end(), lower_network_name.begin(), ::tolower);
    if (!network_map_.count(lower_network_name))
    {
        stringstream err;
        err << "NetworkSelector::select() - network \"" << lower_network_name << "\" not recognized.";
        throw runtime_error(err.str());
    }

    selected_ = lower_network_name;
}


// Coins can be added here
const CoinParams bitcoinParams(
    0xd9b4bef9ul,
    70001,
    "8333",
    0x00,
    0x05,
    "Bitcoin",
    "bitcoin",
    100000000,
    "BTC",
    21000000,
    &sha256_2,
    &sha256_2,
    Coin::CoinBlockHeader(
        1,
        1231006505,
        486604799,
        2083236893,
        uchar_vector(32, 0),
        uchar_vector("4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b")
    )
);
const CoinParams& getBitcoinParams() { return bitcoinParams; }

const CoinParams testnet3Params(
    0x0709110bul,
    70001,
    "18333",
    0x6f,
    0xc4,
    "Testnet3",
    "testnet3",
    100000000,
    "testBTC",
    21000000,
    &sha256_2,
    &sha256_2,
    Coin::CoinBlockHeader(
        1,
        1296688602,
        486604799,
        414098458,
        uchar_vector(32, 0),
        uchar_vector("4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b")
    )
);
const CoinParams& getTestnet3Params() { return testnet3Params; }

const CoinParams litecoinParams(
    0xdbb6c0fbul,
    70002,
    "9333",
    0x30,
    0x05,
    "Litecoin",
    "litecoin",
    100000000,
    "LTC",
    84000000,
    &sha256_2,
    &scrypt_1024_1_1_256,
    Coin::CoinBlockHeader(
        1,
        1317972665,
        0x1e0ffff0,
        2084524493,
        uchar_vector(32, 0),
        uchar_vector("97ddfbbae6be97fd6cdf3e7ca13232a3afff2353e29badfab7f73011edd4ced9")
    )
);
const CoinParams& getLitecoinParams() { return litecoinParams; }

const CoinParams quarkcoinParams(
    0xdd03a5feul,
    70001,
    "11973",
    0x3a,
    0x09,
    "Quarkcoin",
    "quarkcoin",
    100000,
    "QRK",
    0xffffffffffffffffull / 100000,
    &hash9,
    &hash9,
    Coin::CoinBlockHeader(
        112,
        1374408079,
        0x1e0fffff,
        12058113,
        uchar_vector(32, 0),
        uchar_vector("868b2fb28cb1a0b881480cc85eb207e29e6ae75cdd6d26688ed34c2d2d23c776")
    )
);
const CoinParams& getQuarkcoinParams() { return quarkcoinParams; }

}