// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xef;
        pchMessageStart[1] = 0xa9;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0x7c;
        vAlertPubKey = ParseHex("06a54765b96e9056bc6b132a04b94acefeac5d5257fe028e80695c62f7c2f81f85d251a216df3be197653f454852a2d08c6314aad5ca3cbe5616262ca3e7a6feef");
        nDefaultPort = 10024;
        nRPCPort = 10022;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "Australian Government Considers Blockchain Tech for Land Transport, by: Kevin Helms - October 15, 2016"; // Saturday, 15-Oct-16 12:00:00 UTC 
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1476532800, vin, vout, 0); // Saturday, 15-Oct-16 12:00:00 UTC 
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1476532800; // Saturday, 15-Oct-16 12:00:00 UTC 
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 180782;

        /** Genesis Block MainNet */
        /*
        Hashed MainNet Genesis Block Output
        block.hashMerkleRoot == b6602abe6f7422a367781fe8a1a8d8536a286c956b4db296066f9c486a93e25d
        block.nTime = 1476532800
        block.nNonce = 180782
        block.GetHash = 00000ff60784c4c8ceed0866d00de5742529ef3f1911e245f4126c5c293c88cd
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000ff60784c4c8ceed0866d00de5742529ef3f1911e245f4126c5c293c88cd"));
        assert(genesis.hashMerkleRoot == uint256("0xb6602abe6f7422a367781fe8a1a8d8536a286c956b4db296066f9c486a93e25d"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,92);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,110);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,50);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nTargetSpacing = 180; // Initially ~180 Sec during PoW
        if(nBestHeight > nLastPoWBlock) // Scaled down for PoS only phase
        {
          nTargetSpacing = 180;
        }
        if(nBestHeight > nStartPoSBlock) // Scaled up for PoW/PoS twin phase
        {
          if(nBestHeight <= nLastPoWBlock)
          {
            nTargetSpacing = 400;
          }
        }
        nTargetTimespan = 10 * nTargetSpacing;
        nLastPoWBlock = 380005;
        nStartPoSBlock = 3805;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x12;
        pchMessageStart[1] = 0x1a;
        pchMessageStart[2] = 0x52;
        pchMessageStart[3] = 0xb4;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 16);

        vAlertPubKey = ParseHex("06b54765b96e9056bc6b132a04b94acefeac5d5257fe028e80695c62f7c2f81f85d251a216df3af197653f454852a2d08c6314aad5ca3cbe5616262ca3e7a6feef");
        nDefaultPort = 10012;
        nRPCPort = 10018;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 71679;

        /** Genesis Block TestNet */
        /*
        Hashed TestNet Genesis Block Output
        block.hashMerkleRoot == b6602abe6f7422a367781fe8a1a8d8536a286c956b4db296066f9c486a93e25d
        block.nTime = 1476532800
        block.nNonce = 71679
        block.GetHash = 000067596509a7006e9d4d0978441e23ff5e18903b127a4a975833fff92b7b99

        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000067596509a7006e9d4d0978441e23ff5e18903b127a4a975833fff92b7b99"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,93);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,51);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nTargetSpacing = 200;
        nLastPoWBlock = 0x7fffffff;
        nStartPoSBlock = 4500;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0x21;
        pchMessageStart[1] = 0xaf;
        pchMessageStart[2] = 0x56;
        pchMessageStart[3] = 0xbc;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1476533000;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 8;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 19001;
        strDataDir = "regtest";

        /** Genesis Block RegNet */
        /*
        Hashed RegNet Genesis Block Output
        block.hashMerkleRoot == b6602abe6f7422a367781fe8a1a8d8536a286c956b4db296066f9c486a93e25d
        block.nTime = 1476533000
        block.nNonce = 8
        block.GetHash = eeeee246c360bb21810c8283ad3b6874146be2d75987e3a30b69808d999e4464
        */

        assert(hashGenesisBlock == uint256("0xeeeee246c360bb21810c8283ad3b6874146be2d75987e3a30b69808d999e4464"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
