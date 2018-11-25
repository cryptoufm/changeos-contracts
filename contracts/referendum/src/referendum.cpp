#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include "logger.hpp"
#include "referendum.hpp"
#include <string>
#define DEBUG



using namespace eosio;
using namespace std;

using namespace eosio;

class referendum : public eosio::contract {
    public:   
        using contract::contract;
        referendum( account_name self) :
            contract(self),
            petition_index(_self, _self)
            {}

        //referendum(string citizen_uid, string volunteer_id,  datastream<const char*> ds):contract(citizen_uid, volunteer_id, ds) {} 
        
        // @abi action
        void insert(uint64_t citizen_uid, std::string volunteer_id, std::string image_hash) {
            auto iter = petition_index.find( citizen_uid );

            eosio_assert(iter == petition_index.end(), "Citizen vote already casted.");

            auto new_sign = petition_index.emplace( _self, [&]( auto& petition ){
                petition.citizen_uid = citizen_uid;
                petition.volunteer_id = volunteer_id;
                petition.image_hash = image_hash;
            
            });        
        };

        void retrieve(uint64_t citizen_uid) {

            auto iter = petition_index.find( citizen_uid );
            eosio_assert(iter != petition_index.end(), "Citizen vote unavailable.");
            //print(iter);
            
            //return [iter.volunteer_id, iter.image_hash]      
        };

        private:

            // @abi table petition i64
            struct petition {
                uint64_t citizen_uid;
                std::string volunteer_id;
                std::string image_hash;

                uint64_t primary_key() const { return citizen_uid; }

                EOSLIB_SERIALIZE( petition, (citizen_uid)(volunteer_id)(image_hash))
            };
        
            multi_index<N(petition), petition> petition_index;
    
};

EOSIO_ABI( referendum, (insert))
