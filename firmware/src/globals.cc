#include "globals.h"

mutex_t their_usages_mutex;

std::unordered_map<uint16_t, std::unordered_map<uint8_t, std::unordered_map<uint32_t, usage_def_t>>> their_usages;

std::unordered_map<uint16_t, bool> has_report_id_theirs;

std::unordered_map<uint16_t, uint8_t> interface_index;
uint32_t interface_index_in_use = 0;

std::vector<usage_rle_t> our_usages_rle;
std::vector<usage_rle_t> their_usages_rle;

volatile bool need_to_persist_config = false;
volatile bool their_descriptor_updated = false;
volatile bool suspended = false;

bool unmapped_passthrough = true;
uint32_t partial_scroll_timeout = 1000000;
std::vector<mapping_config_t> config_mappings;

uint8_t resolution_multiplier = 0;

std::unordered_map<int8_t, screen_def_t> screens = {
    { -1, (screen_def_t){ .sensitivity = 4000 } },
    { 0, (screen_def_t){ .x = 0, .y = 0, .w = 16000000, .h = 9000000, .sensitivity = 4000 } },
    { 1, (screen_def_t){ .x = 16000000, .y = 0, .w = 16000000, .h = 9000000, .sensitivity = 4000 } },
};

ConstraintMode constraint_mode = ConstraintMode::VISIBLE;
