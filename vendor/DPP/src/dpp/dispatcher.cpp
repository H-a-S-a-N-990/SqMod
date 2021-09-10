/************************************************************************************
 *
 * D++, A Lightweight C++ library for Discord
 *
 * Copyright 2021 Craig Edwards and D++ contributors 
 * (https://github.com/brainboxdotcc/DPP/graphs/contributors)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ************************************************************************************/
#include <dpp/discord.h>
#include <dpp/slashcommand.h>
#include <dpp/dispatcher.h>
#include <dpp/cluster.h>
#include <fmt/format.h>
#include <variant>

#define event_ctor(a, b) a::a(discord_client* client, const std::string &raw) : b(client, raw) {}

namespace dpp {

event_dispatch_t::event_dispatch_t(discord_client* client, const std::string &raw) : from(client), raw_event(raw)
{
}

void interaction_create_t::reply(interaction_response_type t, const message & m) const
{
	from->creator->interaction_response_create(this->command.id, this->command.token, dpp::interaction_response(t, m));
}

void interaction_create_t::reply(interaction_response_type t, const std::string & mt) const
{
	this->reply(t, dpp::message(this->command.channel_id, mt, mt_application_command));
}

void interaction_create_t::get_original_response(command_completion_event_t callback) const
{
	from->creator->post_rest(API_PATH "/webhooks", std::to_string(command.application_id), command.token + "/messages/@original", m_get, "", [callback](json &j, const http_request_completion_t& http) {
		if (callback) {
			callback(confirmation_callback_t("message", message().fill_from_json(&j), http));
		}
	});
}

void interaction_create_t::edit_response(const message & m) const
{
	from->creator->interaction_response_edit(this->command.token, m);
}

void interaction_create_t::edit_response(const std::string & mt) const
{
	this->edit_response(dpp::message(this->command.channel_id, mt, mt_application_command));
}

const command_value& interaction_create_t::get_parameter(const std::string& name) const
{
	/* Dummy STATIC return value for unknown options so we arent returning a value off the stack */
	static command_value dummy_value = {};
	const command_interaction& ci = std::get<command_interaction>(command.data);
	for (auto i = ci.options.begin(); i != ci.options.end(); ++i) {
		if (i->name == name) {
			return i->value;
		}
	}
	return dummy_value;
}

const command_value& button_click_t::get_parameter(const std::string& name) const
{
	/* Buttons don't have parameters, so override this */
	static command_value dummy_b_value = {};
	return dummy_b_value;
}

const command_value& select_click_t::get_parameter(const std::string& name) const
{
	/* Selects don't have parameters, so override this */
	static command_value dummy_b_value = {};
	return dummy_b_value;
}

/* Standard default constructors that call the parent constructor, for events */
event_ctor(guild_join_request_delete_t, event_dispatch_t);
event_ctor(stage_instance_create_t, event_dispatch_t);
event_ctor(stage_instance_delete_t, event_dispatch_t);
event_ctor(log_t, event_dispatch_t);
event_ctor(voice_state_update_t, event_dispatch_t);
event_ctor(interaction_create_t, event_dispatch_t);
event_ctor(button_click_t, interaction_create_t);
event_ctor(select_click_t, interaction_create_t);
event_ctor(guild_delete_t, event_dispatch_t);
event_ctor(channel_delete_t, event_dispatch_t);
event_ctor(channel_update_t, event_dispatch_t);
event_ctor(ready_t, event_dispatch_t);
event_ctor(message_delete_t, event_dispatch_t);
event_ctor(application_command_delete_t, event_dispatch_t);
event_ctor(application_command_create_t, event_dispatch_t);
event_ctor(resumed_t, event_dispatch_t);
event_ctor(guild_role_create_t, event_dispatch_t);
event_ctor(typing_start_t, event_dispatch_t);
event_ctor(message_reaction_add_t, event_dispatch_t);
event_ctor(message_reaction_remove_t, event_dispatch_t);
event_ctor(guild_create_t, event_dispatch_t);
event_ctor(channel_create_t, event_dispatch_t);
event_ctor(message_reaction_remove_emoji_t, event_dispatch_t);
event_ctor(message_delete_bulk_t, event_dispatch_t);
event_ctor(guild_role_update_t, event_dispatch_t);
event_ctor(guild_role_delete_t, event_dispatch_t);
event_ctor(channel_pins_update_t, event_dispatch_t);
event_ctor(message_reaction_remove_all_t, event_dispatch_t);
event_ctor(voice_server_update_t, event_dispatch_t);
event_ctor(guild_emojis_update_t, event_dispatch_t);
event_ctor(presence_update_t, event_dispatch_t);
event_ctor(webhooks_update_t, event_dispatch_t);
event_ctor(guild_member_add_t, event_dispatch_t);
event_ctor(invite_delete_t, event_dispatch_t);
event_ctor(guild_update_t, event_dispatch_t);
event_ctor(guild_integrations_update_t, event_dispatch_t);
event_ctor(guild_member_update_t, event_dispatch_t);
event_ctor(application_command_update_t, event_dispatch_t);
event_ctor(invite_create_t, event_dispatch_t);
event_ctor(message_update_t, event_dispatch_t);
event_ctor(user_update_t, event_dispatch_t);
event_ctor(message_create_t, event_dispatch_t);
event_ctor(guild_ban_add_t, event_dispatch_t);
event_ctor(guild_ban_remove_t, event_dispatch_t);
event_ctor(integration_create_t, event_dispatch_t);
event_ctor(integration_update_t, event_dispatch_t);
event_ctor(integration_delete_t, event_dispatch_t);
event_ctor(guild_member_remove_t, event_dispatch_t);
event_ctor(guild_members_chunk_t, event_dispatch_t);
event_ctor(thread_create_t, event_dispatch_t);
event_ctor(thread_update_t, event_dispatch_t);
event_ctor(thread_delete_t, event_dispatch_t);
event_ctor(thread_list_sync_t, event_dispatch_t);
event_ctor(thread_member_update_t, event_dispatch_t);
event_ctor(thread_members_update_t, event_dispatch_t);
event_ctor(voice_buffer_send_t, event_dispatch_t);
event_ctor(voice_user_talking_t, event_dispatch_t);
event_ctor(voice_ready_t, event_dispatch_t);
event_ctor(voice_receive_t, event_dispatch_t);
event_ctor(voice_track_marker_t, event_dispatch_t);
event_ctor(guild_stickers_update_t, event_dispatch_t);

};
