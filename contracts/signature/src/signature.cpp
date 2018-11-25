#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include "logger.hpp"
#include "signature.hpp"
#include <string>
#define DEBUG



using namespace eosio;
using namespace std;

using namespace eosio;

class vote : public eosio::contract {

  public:   

    using contract::contract;
    // addressbook(string citizen_uid, string volunteer_id,  datastream<const char*> ds):contract(citizen_uid, volunteer_id, ds) {} 
    
    /// @abi action
    void insert(uint64_t citizen_uid, std::string volunteer_id, std::string image_hash) {

        //address_index addresses(signature(citizen_uid));

        signature_index addresses(signature(citizen_uid));

        auto iterator = addresses.find(citizen_uid);

        if( iter == addresses.end() )
        {
            addresses.emplace(citizen_uid,[&](auto& row) {
                
                row.citizen_uid = citizen_uid;
                row.volunteer_id = volunteer_id;
                row.image_hash = image_hash;
            });
        }
        else {
            //The user is in the table
             print("UID already voted\t");
        }
    }
    
    // void getInfo(std::string citizen_uid) {

    //     //address_index addresses(signature(citizen_uid));

    //     _signature signature(_self, _self);

    //     auto sig = signature.find(citizen_uid);

    //     if( sig != signature.end() )
    //     {
    //         print(sig->citizen_uid);
    //         print(sig->volunteer_id);
    //         print(sig->image_hash);
    //     }
    //     else {
    //         //The user is in the table
    //          print("Signature does not exist\t");
    //     }
    // }

    /// @abi table signature i64
    struct signature {
        uint64_t citizen_uid;
        std::string volunteer_id;
        std::string image_hash;

        uint64_t primary_key() const { return citizen_uid; }

        EOSLIB_SERIALIZE(signature,(citizen_uid)(volunteer_id)(image_hash))

    };
  
    typedef eosio::multi_index<"petition"_n, signature> signature_index;
    //typedef eosio::multi_index<N(signature), signature> _signature;   

};

EOSIO_ABI( vote, (insert))
