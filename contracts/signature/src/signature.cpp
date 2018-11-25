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
            addresses.emplace(citizen_uid, [&]( auto& row ) {
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
      std::string citizen_uid;
      std::string volunteer_id;
      std::string image_hash;

      std::string primary_key() const { return citizen_uid; }
    };
  
    typedef eosio::multi_index<"referrendum", signature> address_index;
};


EOSIO_DISPATCH( vote, (upsert))
