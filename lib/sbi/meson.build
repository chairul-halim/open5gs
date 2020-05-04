# Copyright (C) 2019 by Sukchan Lee <acetcom@gmail.com>

# This file is part of Open5GS.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

libsbi_sources = files('''
    path.c
    init.c

    mhd/u_map.c
    mhd/u_response.c
    mhd/u_send_request.c
    mhd/ulfius.c
    mhd/u_request.c

    src/list.c
    src/apiKey.c
    external/cJSON.c
    model/object.c
    model/access_type.c
    model/amf_cond.c
    model/amf_info.c
    model/atsss_capability.c
    model/ausf_info.c
    model/bsf_info.c
    model/change_item.c
    model/change_type.c
    model/chf_info.c
    model/chf_service_info.c
    model/data_set_id.c
    model/default_notification_subscription.c
    model/dnn_smf_info_item.c
    model/dnn_upf_info_item.c
    model/event_id.c
    model/guami.c
    model/guami_list_cond.c
    model/identity_range.c
    model/inline_response_200.c
    model/interface_upf_info_item.c
    model/invalid_param.c
    model/ip_end_point.c
    model/ipv4_address_range.c
    model/ipv6_addr.c
    model/ipv6_prefix.c
    model/ipv6_prefix_range.c
    model/link.c
    model/links_value_schema.c
    model/n1_message_class.c
    model/n2_information_class.c
    model/n2_interface_amf_info.c
    model/network_slice_cond.c
    model/nf_group_cond.c
    model/nf_instance_id_cond.c
    model/nf_profile.c
    model/nf_service.c
    model/nf_service_status.c
    model/nf_service_version.c
    model/nf_status.c
    model/nf_type.c
    model/nf_type_cond.c
    model/notif_condition.c
    model/notification_data.c
    model/notification_event_type.c
    model/notification_type.c
    model/nrf_info.c
    model/nwdaf_event.c
    model/nwdaf_info.c
    model/patch_item.c
    model/patch_operation.c
    model/pcf_info.c
    model/pdu_session_type.c
    model/plmn_id.c
    model/plmn_range.c
    model/plmn_snssai.c
    model/problem_details.c
    model/service_name.c
    model/service_name_cond.c
    model/smf_info.c
    model/snssai.c
    model/snssai_smf_info_item.c
    model/snssai_upf_info_item.c
    model/subscription_data.c
    model/supi_range.c
    model/tac_range.c
    model/tai.c
    model/tai_range.c
    model/transport_protocol.c
    model/udm_info.c
    model/udr_info.c
    model/up_interface_type.c
    model/upf_info.c
    model/uri_scheme.c
'''.split())

libsbi_inc = include_directories('.')

sbi_cc_flags = ['-DOGS_SBI_COMPILATION']

if cc.get_id() == 'gcc' or cc.get_id() == 'clang'
    sbi_cc_flags += cc.get_supported_arguments([
                    '-Wno-strict-prototypes',
                    '-Wno-missing-prototypes',
                    '-Wno-missing-declarations',
                    '-Wno-unused-variable',
                    '-Wno-unused-label',
                    '-Wno-float-equal',
                    '-Wno-discarded-qualifiers',
                    '-Wno-implicit-function-declaration', # FIXME
                    '-Wno-nested-externs', # FIXME
                    '-Wno-int-conversion', # FIXME
                    '-Wno-suggest-attribute=noreturn', # FIXME
    ])
endif

liborcania_dep = cc.find_library('orcania', required : true)
libgnutls_dep = cc.find_library('gnutls', required : true)
libmicrohttpd_dep = dependency('libmicrohttpd')
libcurl_dep = dependency('libcurl')

libsbi = library('ogssbi',
    sources : libsbi_sources,
    version : libogslib_version,
    c_args : sbi_cc_flags,
    include_directories : [libsbi_inc, libinc],
    dependencies : [libcore_dep,
                    liborcania_dep,
                    libgnutls_dep,
                    libmicrohttpd_dep,
                    libcurl_dep],
    install : true)

libsbi_dep = declare_dependency(
    link_with : libsbi,
    include_directories : [libsbi_inc, libinc],
    dependencies : [libcore_dep,
                    liborcania_dep,
                    libgnutls_dep,
                    libmicrohttpd_dep,
                    libcurl_dep])
