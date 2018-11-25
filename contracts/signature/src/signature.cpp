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
    void insert(uid citizen_uid, std::string volunteer_id, std::string image_hash) {

        //address_index addresses(signature(citizen_uid));

        _signature signature(_self,_self);

        auto iter = signature.find(citizen_uid);

        if( iter == signature.end() )
        {
            signature.emplace(_self,[&](auto& signature) {
                
                signature.citizen_uid = citizen_uid;
                signature.volunteer_id = volunteer_id;
                signature.image_hash = image_hash;
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
private:

    /// @abi table signature i64
    struct signature {
        uid citizen_uid;
        std::string volunteer_id;
        std::string image_hash;

        uint64_t primary_key() const { return citizen_uid; }

        EOSLIB_SERIALIZE(signature,(citizen_uid)(volunteer_id)(image_hash))

    };
  
    typedef eosio::multi_index<N(signature), signature> _signature;   

};

EOSIO_ABI( vote, (insert))
