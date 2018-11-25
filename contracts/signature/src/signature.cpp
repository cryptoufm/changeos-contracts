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
    using contract::contract;
    public:   
        referendum( account_name self) :
            contract(self),
            petition(_self, _self)
            {}

        //referendum(string citizen_uid, string volunteer_id,  datastream<const char*> ds):contract(citizen_uid, volunteer_id, ds) {} 
        
        // @abi action
        void insert(uint64_t citizen_uid, std::string volunteer_id, std::string image_hash) {

            auto new_sign = petition_index.emplace( _self, [&]( auto& petition)){
                petition.citizen_uid = citizen_uid;
                petition.volunteer_id = volunteer_id;
                petition.image_hash = image_hash;
            
            };        
        };

        private:

            // @abi table petition i64
            struct petition {
                name citizen_uid;
                std::string volunteer_id;
                std::string image_hash;

                uint64_t primary_key() const { return citizen_uid.value; }

                EOSLIB_SERIALIZE( petition, (citizen_uid)(volunteer_id)(image_hash))
            };
        
            multi_index<N(petition), petition> petition_index;
    
};

EOSIO_ABI( referendum, (insert))
