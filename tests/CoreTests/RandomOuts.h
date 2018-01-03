// Copyright (c) 2011-2016 The UpscaleCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once 

#include "Chaingen.h"

struct GetRandomOutputs : public test_chain_unit_base
{
  GetRandomOutputs();

  // bool check_tx_verification_context(const UpscaleCoin::tx_verification_context& tvc, bool tx_added, size_t event_idx, const UpscaleCoin::Transaction& tx);
  // bool check_block_verification_context(const UpscaleCoin::block_verification_context& bvc, size_t event_idx, const UpscaleCoin::Block& block);
  // bool mark_last_valid_block(UpscaleCoin::core& c, size_t ev_index, const std::vector<test_event_entry>& events);

  bool generate(std::vector<test_event_entry>& events) const;


private:

  bool checkHalfUnlocked(UpscaleCoin::core& c, size_t ev_index, const std::vector<test_event_entry>& events);
  bool checkFullyUnlocked(UpscaleCoin::core& c, size_t ev_index, const std::vector<test_event_entry>& events);

  bool request(UpscaleCoin::core& c, uint64_t amount, size_t mixin, UpscaleCoin::COMMAND_RPC_GET_RANDOM_OUTPUTS_FOR_AMOUNTS_response& resp);

};
