// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x000006e6fa091a20a38fe6f0212d03e5df72b44d76e2eb4246b4d366dbb01faf"))
    (1, uint256("0x0000066df97de78fdde0f1cd5e78cf7ff17e1a8d6cbf4137afa99f1587fe7d2e"))
    (2, uint256("0x00000b7cf8dc27bc4c98c91089adf58f5ec673e022c1b8ea0d5146d13bc49bb7"))
    (61, uint256("0x0000001e7aa6833af7660e4e58d739560af233922fa8f043b103af40d8043ee7"))
    (200, uint256("0x000001b018bb282b454914e42f9653b0e26fb8065562e50cbd9ce63283904b6a"))
    (1000, uint256("0x6ba268b0a5a87360b5942084a03e44b10b99bc9942153843be8f30be9946d709"))
    (5000, uint256("0x7b905329a6adabf53cba6a4c69fe4152a14a1154852f8459e7928f3566a99434"))
    (10000, uint256("0x35f56a42078ed92afa103fa5d8fe0684e0d5f800350f5230e3bf5e56f83fcc08"))
    (15000, uint256("0x278fa794765bcaf37b9b3f61c14584c2957b602cda5512f02a16dda8f702f751"))
    (100000, uint256("0xbc47e4959664446a7ebc294446c2693e3e441eee2748b00defbd9248d498fd7d"))
    (120290, uint256("0xe6fbbf7e0df5c271eab87e05060c6bb4c13a97f0cb9299dbe824a119855f028f"))
    (140000, uint256("0xa7dc9c64e7b7902288c3fa82614edf09e70349f96e2aa71ade15343f15e61e04"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1524769569, // * UNIX timestamp of last checkpoint block
    15000,      // * total number of transactions between genesis and last checkpoint
    //   (the tx=... number in the SetBestChain debug.log lines)
    1400        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x0000040df09b15ba874400ba995f342b82573864b9ee10c255dc4448ce334438"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1523855288,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256("0x001"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1521117300,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xc5;
        pchMessageStart[1] = 0xa2;
        pchMessageStart[2] = 0xe1;
        pchMessageStart[3] = 0xd6;
        vAlertPubKey = ParseHex("045842c614ccb80d184542d6b45a6851f58de36fc898d6a38f32b4b7af28a67e16f2b809c1425c6d95eb8b39aa3e79729bfe59f6854450229ea6572045455962b7");
        nDefaultPort = 9229;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Bifrost starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Bifrost: 1 day
        nTargetSpacing = 1 * 30;  // Bifrost: 1 minute
        nMaturity = 60;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 21000000 * COIN;

        /** Major code base update **/
        nWalletForkBlock = 165437;
        nWalletForkDblBlock = 175437;       // +10000
        nWalletForkResumeBlock = 185437;    // +20000

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 1;
        nZerocoinStartHeight = nWalletForkBlock;
        nZerocoinStartTime = 1533903794;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = nWalletForkBlock; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 500000; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = nWalletForkBlock; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = nWalletForkBlock; //Start enforcing the invalid UTXO's and staking rewards
        nInvalidAmountFiltered = 0*COIN; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = nWalletForkBlock + 500000; //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT
        nEnforceNewSporkKey = 1632109087; //!> Sporks signed after (GMT): Tuesday, May 1, 2018 7:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1632109087; //!> Fully reject old spork key after (GMT): Friday, June 1, 2018 12:00:00 AM

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "Historic Las Vegas Neon Signs Are Shining Again";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("046e4f58d4517c352854232f9f9e021ee812f4b49df81b8c912fbb622c41678353980a8b7de4bddc393ec263ab64dc696f5cbf89ba20d1bb97bcab94bff5c80b4b") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1523854631;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 7065194;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000006e6fa091a20a38fe6f0212d03e5df72b44d76e2eb4246b4d366dbb01faf"));
        assert(genesis.hashMerkleRoot == uint256("0xa6754bc40268cb44d68aa72471945408b68ade886e6b8c5fd18c933d441c087d"));

        vSeeds.push_back(CDNSSeedData("0",  "dnsseed.bifrostcoin.io"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 25);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 85);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 153);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "0470c722d4ace380687fc680fb3af6be9ab49982701bef35ff17d0b79254a2c458e44b40fec77654e27fbeeffb727302d8fb2edb6e915efd722bd5f2a2a56d87f4";
        strSporkKeyOld = "0470c722d4ace380687fc680fb3af6be9ab49982701bef35ff17d0b79254a2c458e44b40fec77654e27fbeeffb727302d8fb2edb6e915efd722bd5f2a2a56d87f4";
        strObfuscationPoolDummyAddress = "BKcUbM3ryKwfdjbd33FnAYFspaxDp4vWLs";
        nStartMasternodePayments = 1523435473; //Wed, 25 Jun 2014 20:36:16 GMT

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zfrost to be stakable

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0x64;
        pchMessageStart[2] = 0x75;
        pchMessageStart[3] = 0x86;
        vAlertPubKey = ParseHex("04207f3e4229bdd4f408e77918571292e149c52b3ff92ef0ec55c5c4e34ae633c331e24e6e70173b03c18549284e29eea43f74d5b32eba631a5d0c277486103c66");
        nDefaultPort = 19229;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Bifrost: 1 day
        nTargetSpacing = 1 * 60;  // Bifrost: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 60;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = 201576;
        nZerocoinStartTime = 1501776000;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 9902850; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 444020; //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1521604800; //!> Sporks signed after Wednesday, March 21, 2018 4:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1522454400; //!> Reject old spork key after Saturday, March 31, 2018 12:00:00 AM GMT

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1523855288;
        genesis.nNonce = 2733486;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000040df09b15ba874400ba995f342b82573864b9ee10c255dc4448ce334438"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 112); // Testnet bifrost addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 29);  // Testnet bifrost script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 240);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet bifrost BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet bifrost BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet bifrost BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "0467b0816d0d1575a98c6c6cf0b4a300f978c090119d7986e2b4798cc457aab21bb15104230de3c256401bc4f04f7a00012c107c227555386ccfb9a4db081cf97d";
        strSporkKeyOld = "0467b0816d0d1575a98c6c6cf0b4a300f978c090119d7986e2b4798cc457aab21bb15104230de3c256401bc4f04f7a00012c107c227555386ccfb9a4db081cf97d";
        strObfuscationPoolDummyAddress = "";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x14;
        pchMessageStart[1] = 0x54;
        pchMessageStart[2] = 0x95;
        pchMessageStart[3] = 0x64;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Bifrost: 1 day
        nTargetSpacing = 1 * 60;        // Bifrost: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1523854631;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 7065194;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 20229;
        //assert(hashGenesisBlock == uint256("0x5f66c55fd2f344b7e18547b69a6520aa5f3eb46f5d4e77444bbf0e93c60d7526"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 30229;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
