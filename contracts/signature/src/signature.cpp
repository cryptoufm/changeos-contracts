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

class vote : public eosio::contract {

  public:   

    using contract::contract;
    // addressbook(string citizen_uid, string volunteer_id,  datastream<const char*> ds):contract(citizen_uid, volunteer_id, ds) {}

    
    void insert(std::string citizen_uid, std::string volunteer_id, std::string image_hash) {
        address_index addresses("lago", Signature(citizen_uid, volunteer_id, image_hash));
        auto iterator = addresses.find(citizen_uid);
        if( iterator == addresses.end() )
        {
            addresses.emplace(citizen_uid, [&]( auto& row ) {
            row.citizen_uid = citizen_uid;
            row.volunteer_id = volunteer_id;
            row.image_hash = image_hash;
            });
        }
        else {
            //The user is in the table
        }
    }


  private:
    struct signature {
      std::string citizen_uid;
      std::string volunteer_id;
      std::string image_hash;

      std::string primary_key() const { return citizen_uid; }
    };
  
    typedef eosio::multi_index<N(referrendum), signature> address_index;
};


EOSIO_DISPATCH( vote, (insert))
