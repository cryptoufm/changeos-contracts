#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include "logger.hpp"
#include "signature.hpp"
#include <string>
#define DEBUG



using namespace eosio;
using namespace std;

using namespace eosio;

class referendum : public eosio::contract {

    public:   

        using contract::contract;

        //referendum(string citizen_uid, string volunteer_id,  datastream<const char*> ds):contract(citizen_uid, volunteer_id, ds) {} 
        
        // @abi action
        void add_signature(uint64_t citizen_uid, std::string volunteer_id, std::string image_hash) {

            auto new_sign = petition_index.emplace( _self, [&]( auto& petition_sign)){
                petition_sign.citizen_uid = citizen_uid;
                petition_sign.volunteer_id = volunteer_id;
                petition_sign.image_hash = image_hash;
            
            }        
        }

        private:

            // @abi table petition_sign i64
            struct petition_sign {
                name citizen_uid;
                std::string volunteer_id;
                std::string image_hash;

                uint64_t primary_key() const { return citizen_uid.value; }

                EOSLIB_SERIALIZE( petition_sign, (citizen_uid)(volunteer_id)(image_hash))
            };
        
            multi_index<N(petition_sign), petition_sign> petition_index;
    
};

EOSIO_ABI( vote, (add_signature))
