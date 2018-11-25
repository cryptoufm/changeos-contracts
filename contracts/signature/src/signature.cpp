#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <map>
#include <iterator>
#include <iostream>
#include <string>
#define DEBUG

#include "logger.hpp"
#include "signature.hpp"

using namespace eosio;
using namespace std;

using namespace eosio;

class [[eosio::contract]] vote : public eosio::contract {

  public:   

    using contract::contract;
    addressbook(name receiver, name code,  datastream<const char*> ds): contract(receiver, code, ds) {}

    [[eosio::action]]
    void upsert(std::string citizen_uid, std::string volunteer_id, std::string image_hash) {
        address_index addresses(_code, citizen_uid);
        auto iterator = addresses.find(citizen_uid);
        if( iterator == addresses.end() )
        {
            addresses.emplace(user, [&]( auto& row ) {
            row.key = citizen_uid;
            row.volunteer_id = volunteer_id;
            row.image_hash = image_hash;
        });
        }
        else {
            //The user is in the table
        }
    }


  private:
    struct [[eosio::table]] signature {
      citizen_uid key;
      std::string volunteer_id;
      std::string image_hash;

      uint64_t primary_key() const { return key.value;}
    };
  
    typedef eosio::multi_index<"referrendum"_n, signature> address_index;
};


EOSIO_DISPATCH( vote, (upsert))
