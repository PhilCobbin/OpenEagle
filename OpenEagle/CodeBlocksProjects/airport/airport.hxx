/***************************************************************
 * Name:      airport.hxx
 * Purpose:   read, summarize, and generate files related to the
 * FAA apt.txt file et al, part of the NASR 56 day cycle database
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2021-04-11
 * Copyright: Philip Cobbin (cobbin.com)
 * License    GPLv3 see: https://www.gnu.org/licenses/gpl-3.0.htm
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later versio
 *
 * This library is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public Lice
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 **************************************************************/
#ifndef AIRPORT_H
#define AIRPORT_H
#include <stdio.h>
#include "../system_io/system_io.hxx"
#include "../avl_tree/avl_tree.hxx"
#include "../OpenEaglePaths/OpenEaglePaths.hxx"

#define SG_FEET_TO_METER    0.3048
class airport
{
  public:
    bool terminal_io;
    OpenEaglePaths *paths;
    std::string command;

    void read_airport_data();
    void read_tower_data();
    void read_ils_data();
    void read_awos_data();
    void read_nav_data();
    void read_NASR_apt_dat(char * filename);
    void read_NASR_nav_data(char * filename);
    void read_fix_data();
    void read_NASR_fix_data(char * filename);

    void set_terminal_io(bool do_terminal_io);

    void generate_airport_files();
    void generate_airport_files(char * path);
    void generate_nav_files();
    void generate_flightgear_apt_dat(char * flighgear_apt_path);
    void generate_flightgear_apt_dat();
    void generate_flightgear_nav_dat(char * flightgear_nav_path);
    void generate_flightgear_metar_dat();
    void generate_flightgear_fix_dat();
    void generate_flightgear_fix_dat(char * flightgear_fix_path);

    void generate_flightgear_nav_dat();


    void free_airport_data();
    bool lookup_airport_elevation(char * apt,double *elevation);
    bool lookup_airport_and_set_current(char * apt);
    bool lookup_airport_and_set_current_by_lfsn(char * lfsn);
    char * get_airport_type();
    char * get_location_identifier();
    char * get_airport_effective_date();

    int prot_alt_freq_to_miles();
    ///demographics
    char * get_faa_region_code();
    char * get_faa_district_office();
    char * get_st();
    char * get_stname();
    char * get_county();
    char * get_county_st();
    char * get_city();
    char * get_name();
    /// OWNERSHIP
    char * get_ownership_type();
    char * get_facility_use();
    char * get_own_name();
    char * get_own_addr();
    char * get_own_city();
    char * get_own_phone();
    char * get_mgr_name();
    char * get_mgr_addr();
    char * get_mgr_city();
    char * get_mgr_phone();
     /// GEOGRAPHIC DATA
    char * get_airport_latitude_formatted();
    char * get_airport_latitude_seconds();
    char * get_airport_longitude_formatted();
    char * get_airport_longitude_seconds();
    char * get_airport_ref_determ_method();
    char * get_airport_elevation();
    char * get_airport_elevation_method();
    char * get_airport_mag_var();
    char * get_airport_mag_var_epoch_yr();
    char * get_traffic_pattern_altitude();
    char * get_section_chart();
    char * get_dist_from_business();
    char * get_dir_from_business();
    char * get_land_area();
    /// FAA SERVICES
    char * get_boundary_artcc();
    char * get_boundary_artcc_faa();
    char * get_boundary_artcc_name();
    char * get_resp_artcc_rep_id();
    char * get_resp_artcc_faa();
    char * get_resp_artcc_name();
    char * get_tie_in_phys();
    char * get_tie_in_id();
    char * get_tie_in_name();
    char * get_local_phone();
    char * get_toll_free_phone();
    char * get_alt_fss_id();
    char * get_alt_fss_name();
    char * get_alt_fss_toll_free();
    char * get_notam_id();
    char * get_notam_available();
    /// FEDERAL STATUS
    char * get_airport_activ_data();
    char * get_airport_status_code();
    char * get_airport_arf_cert();
    char * get_NPIAS_FEDERAL_code();
    char * get_airport_airspace_analysis();
    char * get_airport_customs_poe();
    char * get_airport_customs_landing();
    char * get_military_civil_joint_use();
    char * get_military_landing_rights();
    ///AIRPORT INSPECTION DATA
    char * get_airport_insp_method();
    char * get_airport_insp_agency();
    char * get_airport_last_inspect();
    char * get_airport_last_info_req();
    /// AIRPORT SERVICES
    char * get_fuel_types();
    char * get_airframe_repair();
    char * get_powerplant_repair();
    char * get_bottled_oxy();
    char * get_bulk_oxy();
    /// AIRPORT FACILITIES
    char * get_light_sched();
    char * get_beacon_light_sched();
    char * get_airport_has_tower();
    char * get_unicom();
    char * get_ctaf();
    char * get_segment_circle_marker();
    char * get_lens_color();
    char * get_landing_fee();
    char * get_medical_use();
    /// BASED AIRCRAFT
    char * get_sega();
    char * get_mega();
    char * get_jetga();
    char * get_gaheli();
    char * get_glider();
    char * get_military();
    char * get_ultralight();
    /// ANNUAL OPERATIONS
    char * get_cab_carriers();
    char * get_commuter();
    char * get_air_taxi();
    char * get_ga_ops();
    char * get_ga_itinerant();
    char * get_mil_ops();
    char * get_ending_date();
    /// ADDITIONAL AIRPORT DATA
    char * get_pos_source();
    char * get_pos_source_date();
    char * get_apt_elev_source();
    char * get_apt_elev_source_date();
    char * get_contract_fuel();
    char * get_transient_store();
    char * get_other_ac_services();
    char * get_wind_indicator();
    char * get_airport_official_icao();
    char * get_min_op_network();


    /// attendance records
    bool have_attendance_records();
    bool next_attendance_record();
    char * get_att_lfsn();
    char * get_att_st();
    char * get_att_sn();
    char * get_att_sched();


    /// arrest records
    bool have_arrest_records();
    bool next_arrest_record();
    char * get_ars_lfsn();
    char * get_ars_lfst();
    char * get_ars_runway();
    char * get_ars_runway_end();
    char * get_ars_type();

    /// remark records
    bool have_remark_records();
    bool next_remark_record();
    char * get_rmk_lfsn();
    char * get_rmk_lfst();
    char * get_rmk_name();
    char * get_rmk_text();

    /// runway records
    bool have_runway_records();
    bool next_runway_record();
    char * get_rwlanding_facility_site_number();
    char * get_rw_st();
    char * get_runway_id();
    /// COMMON RUNWAY DATA
    char * get_runway_length();
    char * get_runway_width();
    char * get_runway_surface_type_cond();
    char * get_runway_surface_treatment();
    char * get_runway_pcn();
    char * get_runway_light_edge_intensity();
    /// BASE END INFORMATION
    char * get_b_id();
    char * get_b_true_alignment();
    char * get_b_ils_type();
    char * get_b_rh_traffic();
    char * get_b_rwy_markings();
    char * get_b_rwy_condition();
    /// BASE END GEOGRAPHIC DATA
    char * get_b_latitude();
    char * get_b_latitude_seconds();
    char * get_b_longitude();
    char * get_b_longitude_seconds();
    char * get_b_elevation();
    char * get_b_threshold_xheight();
    char * get_b_glide_slope();
    char * get_b_dt_latitude();
    char * get_b_dt_latitude_seconds();
    char * get_b_dt_longitude();
    char * get_b_dt_longitude_seconds();
    char * get_b_dt_elevation();
    char * get_b_dt_length();
    char * get_b_dt_elev_at_td();
    /// BASE END LIGHTING DATA
    char * get_b_glide_slope_ind();
    char * get_b_rvr();
    char * get_b_rvv();
    char * get_b_approach_lights();
    char * get_b_reil();
    char * get_b_ctr_ln_lights();
    char * get_b_td_lights();
    /// BASE END OBJECT DATA
    char * get_b_object();
    char * get_b_marked_lighted();
    char * get_b_faa_cfr_77();
    char * get_b_clearance_slope();
    char * get_b_height_above_rwy();
    char * get_b_dist_from_rwy();
    char * get_b_center_line_offset();
    /// RECIPROCAL END INFORMATION
    char * get_r_id();
    char * get_r_true_alignment();
    char * get_r_ils_type();
    char * get_r_rh_traffic();
    char * get_r_rwy_markings();
    char * get_r_rwy_condition();
    /// RECIPROCAL END GEOGRAPHIC DATA
    char * get_r_latitude();
    char * get_r_latitude_seconds();
    char * get_r_longitude();
    char * get_r_longitude_seconds();
    char * get_r_elevation();
    char * get_r_threshold_xheight();
    char * get_r_glide_slope();
    char * get_r_dt_latitude();
    char * get_r_dt_latitude_seconds();
    char * get_r_dt_longitude();
    char * get_r_dt_longitude_seconds();
    char * get_r_dt_elevation();
    char * get_r_dt_length();
    char * get_r_dt_elev_at_td();
    /// RECIPROCAL END LIGHTING DATA
    char * get_r_glide_slope_ind();
    char * get_r_rvr();
    char * get_r_rvv();
    char * get_r_approach_lights();
    char * get_r_reil();
    char * get_r_ctr_ln_lights();
    char * get_r_td_lights();
    /// RECIPROCAL END OBJECT DATA
    char * get_r_object();
    char * get_r_marked_lighted();
    char * get_r_faa_cfr_77();
    char * get_r_clearance_slope();
    char * get_r_height_above_rwy();
    char * get_r_dist_from_rwy();
    char * get_r_center_line_offset();
    ///ADDITIONAL COMMON RUNWAY DATA
    char * get_length_src();
    char * get_length_date();
    char * get_single_wheel_cap();
    char * get_dual_wheel_cap();
    char * get_dual_wheel_tandem_cap();
    char * get_two_duel_wheel_tandem_cap();
    /// ADDITIONAL BASE END DATA
    char * get_b_runway_end_gradient();
    char * get_b_runway_end_gradient_dir();
    char * get_b_runway_end_pos_src();
    char * get_b_runway_end_pos_date();
    char * get_b_runway_end_elev_src();
    char * get_b_runway_end_elev_src_date();
    char * get_b_dt_pos_src();
    char * get_b_dt_pos_src_date();
    char * get_b_dt_elev_src();
    char * get_b_dt_elev_src_date();
    char * get_b_td_elev_src();
    char * get_b_td_elev_src_date();
    char * get_b_tora();
    char * get_b_toda();
    char * get_b_asda();
    char * get_b_lda();
    char * get_b_lahso();
    char * get_b_id_int_rw();
    char * get_b_id_desc_ent();
    char * get_b_lat_lahso();
    char * get_b_lat_lahso_seconds();
    char * get_b_lon_lahso();
    char * get_b_lon_lahso_seconds();
    char * get_b_latlon_lahso_src();
    char * get_b_latlon_lahso_src_date();
    /// ADDITIONAL RECIPROCAL END DATA
    char * get_r_runway_end_gradient();
    char * get_r_runway_end_gradient_dir();
    char * get_r_runway_end_pos_src();
    char * get_r_runway_end_pos_date();
    char * get_r_runway_end_elev_src();
    char * get_r_runway_end_elev_src_date();
    char * get_r_dt_pos_src();
    char * get_r_dt_pos_src_date();
    char * get_r_dt_elev_src();
    char * get_r_dt_elev_src_date();
    char * get_r_td_elev_src();
    char * get_r_td_elev_src_date();
    char * get_r_tora();
    char * get_r_toda();
    char * get_r_asda();
    char * get_r_lda();
    char * get_r_lahso();
    char * get_r_id_int_rw();
    char * get_r_id_desc_ent();
    char * get_r_lat_lahso();
    char * get_r_lat_lahso_seconds();
    char * get_r_lon_lahso();
    char * get_r_lon_lahso_seconds();
    char * get_r_latlon_lahso_src();
    char * get_r_latlon_lahso_src_date();

    /// twr1 records
    bool have_twr1_record();
    char * get_term_com_fac_id();
    char * get_info_effect_date();
      /// Landing Facility(Airport) Data
    char * get_lfsn();     //  (indext to airport)
    char * get_faa_reg_code();
    char * get_assoc_st_name();
    char * get_assoc_st();
    char * get_assoc_city_name();
    char * get_offic_apt_name();
    char * get_latitude();
    char * get_latitude_seconds();
    char * get_longitude();
    char * get_longitude_seconds();
    char * get_tie_in_fss();
    char * get_tie_in_fss_name();
      /// Terminal Communications Facility Data
    char * get_fac_type();
    char * get_num_hours();
    char * get_num_hours_code();
    char * get_master_apt_id();
    char * get_master_apt_name();
    char * get_dir_find_eq();
      /// Terminal Communications Facility Off Airport
    char * get_assoc_land_fac();
    char * get_accoc_city();
    char * get_st_prov();
    char * get_st_county();
    char * get_country_st();
    char * get_faa_reg_code_off_apt();
      /// latitude/longitude data
         /// airport surveillance radar
    char * get_as_rad_lat();
    char * get_as_rad_lat_seconds();
    char * get_as_rad_lon();
    char * get_as_rad_lon_seconds();
         /// direction finding antenna
    char * get_dfa_rad_lat();
    char * get_dfa_rad_lat_seconds();
    char * get_dfa_rad_lon();
    char * get_dfa_rad_lon_seconds();
      /// Operator Data
    char * get_twr();
    char * get_mil_ops_data();
    char * get_p_app_cntrl();
    char * get_s_app_cntrl();
    char * get_p_dep_cntrl();
    char * get_s_dep_cntrl();
      /// radio call data
    char * get_pilot_to_twr();
    char * get_mill_ops_call();
    char * get_p_app_cntr_call();
    char * get_p_take_over_cntrl_call();
    char * get_p_dep_cntr();
    char * get_d_take_over_dep_cntrl();

    bool have_twr2_record();
    char * get_ident();
    char * get_pmsv();
    char * get_macp();
    char * get_dyly();
    char * get_p_app();
    char * get_s_app();
    char * get_p_dep();
    char * get_s_dep();
    char * get_twr2_twr();

    bool have_twr3_records();
    bool next_twr3_record();
    char * get_twr3_ident();
    char * get_twr3_freq(int i);
    char * get_twr3_use(int i);
    char * get_freq_not_trunc(int i);

    bool have_twr4_records();
    bool next_twr4_record();
    char * get_twr4_ident();
    char * get_service();

    bool have_twr5_record();
    char * get_twr5_ident();
    char * get_p_apr_call();
    char * get_s_apr_call();
    char * get_p_dep_call();
    char * get_s_dep_call();
    char * get_radar_type(int i);
    char * get_radar_hrs(int i);

    bool have_twr6_records();
    bool next_twr6_record();
    char * get_twr6_ident();
    char * get_twr6_elem_nbr();
    char * get_twr6_remark();

    bool have_twr7_records();
    bool next_twr7_record();
    char * get_twr7_ident();
    char * get_twr7_sat_freq();
    char * get_twr7_sat_use();
    char * get_twr7_apt_site_nbr();
    char * get_twr7_apt_id();
    char * get_twr7_faa_reg();
    char * get_twr7_st_name();
    char * get_twr7_st();
    char * get_twr7_city();
    char * get_twr7_arpt_name();
    char * get_twr7_lat();
    char * get_twr7_lat_seconds();
    char * get_twr7_lon();
    char * get_twr7_lon_seconds();
    char * get_twr7_fss_id();
    char * get_twr7_fss_name();
      /// Master Airport Information
    char * get_twr7_m_arpt_id();
    char * get_twr7_m_faa_reg();
    char * get_twr7_m_st_name();
    char * get_twr7_m_st();
    char * get_twr7_m_city();
    char * get_twr7_m_arpt_name();
    char * get_twr7_m_sat_freq();

    bool have_twr8_record();
    char *get_twr8_ident();
    char *get_twr8_class_b();
    char *get_twr8_class_c();
    char *get_twr8_class_d();
    char *get_twr8_class_e();
    char *get_twr8_hours();

    bool have_twr9_records();
    bool next_twr9_record();
    char * get_twr9_ident();
    char * get_twr9_sn();
    char * get_twr9_hours();
    char * get_twr9_purpose();
    char * get_twr9_phone();

    bool have_awos1_record();
    bool next_awos1_record();
    char * get_awos1_wx_sensor_ident();
    char * get_awos1_wx_sensor_type();
    char * get_awos1_commisioning_status();
    char * get_awos1_commisioning_date();
    char * get_awos1_navaid_flag();
    char * get_awos1_lat();
    char * get_awos1_lon();
    char * get_awos1_elevation();
    char * get_awos1_survey_method();
    char * get_awos1_frequency();
    char * get_awos1_frequency2();
    char * get_awos1_phone();
    char * get_awos1_phone2();
    char * get_awos1_lfsn();
    char * get_awos1_city();
    char * get_awos1_st();
    char * get_awos1_info_eff_date();

    bool have_awos2_records();
    bool next_awos2_record();
    char * get_awos2_wx_sensor_ident();
    char * get_awos2_wx_sensor_type();
    char * get_awos2_remarks();

    /// ILS RECORDS
    /// ILS1 RECORD
    bool have_apt_ils_records();
    bool next_apt_ils_record();
    bool have_ils1_records();
    bool next_ils1_record();
    bool have_ils2_record();
    bool have_ils3_record();
    bool have_ils4_record();
    bool have_ils5_records();
    bool next_ils5_record();
    bool have_ils6_records();
    bool next_ils6_record();

      /// ILS AIRPORT/RUNWAY INFORMATION
    char * get_ils1_lfsn();
    char * get_ils1_rwy_end();
    char * get_ils1_type();
    char * get_ils1_id_code();
    char * get_ils1_eff_date();
    char * get_ils1_apt_name();
    char * get_ils1_city();
    char * get_ils1_st();
    char * get_ils1_state_name();
    char * get_ils1_faa_reg();
    char * get_ils1_apt_id();
    char * get_ils1_length();
    char * get_ils1_width();
      /// ILS SYSTEM INFORMATION
    char * get_ils1_cat();
    char * get_ils1_own_name();
    char * get_ils1_fac_oper();
    char * get_ils1_app_bearing_mag();
    char * get_ils1_mag_var();

    /// ILS2 RECORD /// LOCALIZER DATA
    char * get_ils2_lfsn();
    char * get_ils2_rwy_end();
    char * get_ils2_type();
    char * get_ils2_status();
    char * get_ils2_eff_date();
    char * get_ils2_lat_ant();
    char * get_ils2_lat_ant_seconds();
    char * get_ils2_lon_ant();
    char * get_ils2_lon_ant_seconds();
    char * get_ils2_lat_lon_code();
    char * get_ils2_dist_frm_app_end();
    char * get_ils2_dist_frm_rnwy_cl();
    char * get_ils2_dir_of_ant_frm_rnwy();
    char * get_ils2_src_dist_info();
    char * get_ils2_elev();
    char * get_ils2_freq_mhz();
    char * get_ils2_back_crs_status();
    char * get_ils2_course_width();
    char * get_ils2_width_at_threshold();
    char * get_ils2_dist_from_stop();
    char * get_ils2_dir_from_stop();
    char * get_ils2_serv_code();

    /// ILS3 RECORD///GLIDE SLOPE DATA
    char * get_ils3_lfsn();
    char * get_ils3_rwy_end();
    char * get_ils3_type();
    char * get_ils3_status();
    char * get_ils3_eff_date();
    char * get_ils3_lat_ant();
    char * get_ils3_lat_ant_seconds();
    char * get_ils3_lon_ant();
    char * get_ils3_lon_ant_seconds();
    char * get_ils3_lat_lon_code();
    char * get_ils3_dist_frm_app_end();
    char * get_ils3_dist_frm_rnwy_cl();
    char * get_ils3_dir_of_ant_frm_rnwy();
    char * get_ils3_src_dist_info();
    char * get_ils3_elev();
    char * get_ils3_gsclass();
    char * get_ils3_angle();
    char * get_ils3_freq();
    char * get_ils3_adj_elev();

    /// ILS4  ///DISTANCE MEASURING EQUIPMENT (DME) DATA
    char * get_ils4_lfsn();
    char * get_ils4_rwy_end();
    char * get_ils4_type();
    char * get_ils4_status();
    char * get_ils4_eff_date();
    char * get_ils4_lat_ant();
    char * get_ils4_lat_ant_seconds();
    char * get_ils4_lon_ant();
    char * get_ils4_lon_ant_seconds();
    char * get_ils4_lat_lon_code();
    char * get_ils4_dist_frm_app_end();
    char * get_ils4_dist_frm_rnwy_cl();
    char * get_ils4_dir_of_ant_frm_rnwy();
    char * get_ils4_src_dist_info();
    char * get_ils4_elev();
    char * get_ils4_channel();
    char * get_ils4_dist_frm_stop();

    /// ILS5  ///MARKER BEACON DATA
    char * get_ils5_lfsn();
    char * get_ils5_rwy_end();
    char * get_ils5_type();
    char * get_ils5_marker_type();
    char * get_ils5_status();
    char * get_ils5_eff_date();
    char * get_ils5_lat_ant();
    char * get_ils5_lat_ant_seconds();
    char * get_ils5_lon_ant();
    char * get_ils5_lon_ant_seconds();
    char * get_ils5_lat_lon_code();
    char * get_ils5_dist_frm_app_end();
    char * get_ils5_dist_frm_rnwy_cl();
    char * get_ils5_dir_of_ant_frm_rnwy();
    char * get_ils5_src_dist_info();
    char * get_ils5_elev();
    char * get_ils5_fac_type();
    char * get_ils5_loc_id();
    char * get_ils5_name();
    char * get_ils5_freq();
    char * get_ils5_navaid_type();
    char * get_ils5_low_ndb_status();
    char * get_ils5_serv_provided();

    /// ILS6  /// REMARKS

    char * get_ils6_lfsn();
    char * get_ils6_rwy_end();
    char * get_ils6_type();
    char * get_ils6_remarks();

    /// FIX records

    /// CHARTING TYPES
    bool have_fix5_records();
    bool get_next_fix5_record();
    char * get_fix5_fix_id();
    char * get_fix5_fix_st_name();
    char * get_fix5_ICAO_reg();
    char * get_fix5_chart();

    /// REMARKS
    bool have_fix4_records();
    bool get_next_fix4_record();
    char * get_fix4_fix_id();
    char * get_fix4_fix_st_name();
    char * get_fix4_ICAO_reg();
    char * get_fix4_label();
    char * get_fix4_remark();

    /// ILS MAKEUP TEXT
    bool have_fix3_records();
    bool get_next_fix3_record();
    char * get_fix3_fix_id();
    char * get_fix3_fix_st_name();
    char * get_fix3_ICAO_reg();
    char * get_fix3_loc_id();

    /// NAVAID MAKEUP TEXT
    bool have_fix2_records();
    bool get_next_fix2_record();
    char * get_fix2_fix_id();
    char * get_fix2_fix_st_name();
    char * get_fix2_ICAO_reg();
    char * get_fix2_loc_id();

    ///  BASIC FIX DATA
    bool have_fix1_records();
    bool get_next_fix1_record();
    char * get_fix1_fix_id();
    char * get_fix1_fix_st_name();
    char * get_fix1_ICAO_reg();
    char * get_fix1_lat();
    char * get_fix1_lon();
    char * get_fix1_civil_cat();
    char * get_fix1_ident_fac();
    char * get_fix1_apt_rwy_id();
    char * get_fix1_prev_name();
    char * get_fix1_charting();
    char * get_fix1_published();
    char * get_fix1_use();
    char * get_fix1_NAS_id();
    char * get_fix1_high_juris();
    char * get_fix1_low_juris();
    char * get_fix1_country_name();
    char * get_fix1_pitch_flg();
    char * get_fix1_catch_flg();
    char * get_fix1_sua_flg();

    /// NAV records
    /// VOR RECEIVER CHECKPOINTS ASSOC W NAVAID
    bool have_nav6_records();
    bool get_next_nav6_record();
    char * get_nav6_nav_fac_id();
    char * get_nav6_fac_type();
    char * get_nav6_air_grnd();
    char * get_nav6_brng_of_chk_pnt();
    char * get_nav6_alt_only();
    char * get_nav6_apt_id();
    char * get_nav6_st();
    char * get_nav6_narrative();
    char * get_nav6_description();

    ///    FAN MARKERS ASSOC W NAVAID
    bool have_nav5_records();
    bool get_next_nav5_record();
    char * get_nav5_nav_fac_id();
    char * get_nav5_fac_type();
    char * get_nav5_fm_names();
    char * get_nav5_fm_extra_names();

    /// HOLDING PATTERNS (HPF) ASSOC W NAVAID
    bool have_nav4_records();
    bool get_next_nav4_record();
    char * get_nav4_nav_fac_id();
    char * get_nav4_fac_type();
    char * get_nav4_hp_names();
    char * get_nav4_hp_nbr();
    char * get_nav4_extra_hp();

    /// COMPULSORY AND NON-COMPUSORY AIRSPACE FIXES ASSOC W NAVAID
    bool have_nav3_records();
    bool get_next_nav3_record();
    char * get_nav3_nav_fac_id();
    char * get_nav3_fac_type();
    char * get_nav3_fixes();
    char * get_nav3_extra_fixes();


    /// NAVAID REMARKS
    bool have_nav2_records();
    bool get_next_nav2_record();
    char * get_nav2_nav_fac_id();
    char * get_nav2_fac_type();
    char * get_nav2_remarks();

    /// BASIC NAVAID INFORMATION
    bool have_nav1_records();
    bool get_next_nav1_record();
    char * get_nav1_nav_fac_id();
   // char * get_nav1_nav_fac_id();
    char * get_nav1_official_fac_id();
    char * get_nav1_eff_date();
    char * get_nav1_name();
    char * get_nav1_city();
    char * get_nav1_state_name();
    char * get_nav1_st();
    char * get_nav1_faa_reg();
    char * get_nav1_country_other();
    char * get_nav1_other_postal();
    char * get_nav1_owner();
    char * get_nav1_oper_name();
    char * get_nav1_com_sys_use();
    char * get_nav1_public_use();
    char * get_nav1_nav_class();
    char * get_nav1_hours();
    char * get_nav1_artcc_h_bndry();
    char * get_nav1_name_h_artcc();
    char * get_nav1_artcc_l_bndry();
    char * get_nav1_name_l_artcc();
      /// GEOGRAPHIC POSITION DATA
    char * get_nav1_lat();
    char * get_nav1_lat_seconds();
    char * get_nav1_lon();
    char * get_nav1_lon_seconds();
    char * get_nav1_accuracy();
    char * get_nav1_lat_tacan();
    char * get_nav1_lat_tacan_seconds();
    char * get_nav1_lon_tacan();
    char * get_nav1_lon_tacan_seconds();
    char * get_nav1_elevation();
    char * get_nav1_mag_var();
    char * get_nav1_mag_epoch_yr();
      /// FACILITIES/FEATURES OF NAVAID
    char * get_nav1_voice();
    char * get_nav1_watts();
    char * get_nav1_auto_voice_id();
    char * get_nav1_mon_cat();
    char * get_nav1_radio_call();
    char * get_nav1_channel();
    char * get_nav1_freq();
    char * get_nav1_fan_id();
    char * get_nav1_fan_type();
    char * get_nav1_tr_bearng_fm();
    char * get_nav1_prot_alt_freq();
    char * get_nav1_lo_alt_use();
    char * get_nav1_z_marker();
    char * get_nav1_twx_bx_hrs();
    char * get_nav1_twx_wx_ph();
    char * get_nav1_fss_ident();
    char * get_nav1_fss_name();
    char * get_nav1_op_hrs();
    char * get_nav1_notam_ident();
      /// CHARTING DATA
    char * get_nav1_quad_id_rng_brg();
      /// NAVAID STATUS
    char * get_nav1_nav_status();
      /// PITCH, CATCH AND SUA/ATCAA FLAGS
    char * get_nav1_pitch_flg();
    char * get_nav1_catch_flg();
    char * get_nav1_sua_flg();
    char * get_nav1_rest_flg();
    char * get_nav1_hiwas_flg();
    char * get_nav1_tweb_restrict();

    std::string INFORMATION_EFFECTIVE_DATE;

  private:

    /// FIX records

    struct fix5_record { /// CHARTING TYPES
      struct fix5_record * next_fix5;
      char fix_id[31];
      char fix_st_name[31];
      char ICAO_reg[3];
      char chart[23];
    };

    struct fix4_record { /// REMARKS
      struct fix4_record * next_fix4;
      char fix_id[31];
      char fix_st_name[31];
      char ICAO_reg[3];
      char label[101];
      char remark[301];

    };

    struct fix3_record { /// ILS MAKEUP TEXT
      struct fix3_record * next_fix3;
      char fix_id[31];
      char fix_st_name[31];
      char ICAO_reg[3];
      char loc_id[24];
    };

    struct fix2_record {  /// NAVAID MAKEUP TEXT
      struct fix2_record * next_fix2;
      char fix_id[31];
      char fix_st_name[31];
      char ICAO_reg[3];
      char loc_id[24];
    };

    struct fix1_record { ///  BASIC FIX DATA
      struct fix1_record * next_fix1;
      struct fix2_record * fix2_list;
      struct fix3_record * fix3_list;
      struct fix4_record * fix4_list;
      struct fix5_record * fix5_list;
      struct fix6_record * fix6_list;
      char fix_id[31];
      char fix_st_name[31];
      char ICAO_reg[3];
      char lat[15];
      char lon[15];
      char civil_cat[4];
      char ident_fac[23];
      char apt_rwy_id[23];
      char prev_name[34];
      char charting[39];
      char published[2];
      char use[16];
      char NAS_id[6];
      char high_juris[5];
      char low_juris[5];
      char country_name[31];
      char pitch_flg[2];
      char catch_flg[2];
      char sua_flg[2];
    };


    /// NAV records

    struct nav6_record {  /// VOR RECEIVER CHECKPOINTS ASSOC W NAVAID
      struct nav6_record * next_nav6;
      char nav_fac_id[5];
      char fac_type[21];
      char air_grnd[3];
      char brng_of_chk_pnt[4];
      char alt_only[6];
      char apt_id[5];
      char st[3];
      char narrative[76];
      char description[76];
    };

    struct nav5_record {  ///    FAN MARKERS ASSOC W NAVAID
      struct nav5_record * next_nav5;
      char nav_fac_id[5];
      char fac_type[21];
      char fm_names[31];
      char fm_extra_names[691];
    };

    struct nav4_record {  /// HOLDING PATTERNS (HPF) ASSOC W NAVAID
      struct nav4_record * next_nav4;
       char nav_fac_id[5];
       char fac_type[21];
       char hp_names[81];
       char hp_nbr[4];
       char extra_hp[665];
    };

    struct nav3_record {  /// COMPULSORY AND NON-COMPUSORY AIRSPACE FIXES ASSOC W NAVAID
      struct nav3_record * next_nav3;
      char nav_fac_id[5];
      char fac_type[21];
      char fixes[37];
      char extra_fixes[721];
    };

    struct nav2_record { /// NAVAID REMARKS
      struct nav2_record * next_nav2;
      char nav_fac_id[5];
      char fac_type[21];
      char remarks[601];
    };

    struct nav1_record {  /// BASIC NAVAID INFORMATION
      struct nav1_record * next_nav1;
      struct nav2_record * nav2_list;
      struct nav3_record * nav3_list;
      struct nav4_record * nav4_list;
      struct nav5_record * nav5_list;
      struct nav6_record * nav6_list;
      char nav_fac_id[5];
      char fac_type[21];
      char official_fac_id[5];
      char eff_date[11];
      char name[31];
      char city[41];
      char state_name[31];
      char st[3];
      char faa_reg[4];
      char country_other[31];
      char other_postal[3];
      char owner[51];
      char oper_name[51];
      char com_sys_use[2];
      char public_use[2];
      char nav_class[12];
      char hours[12];
      char artcc_h_bndry[5];
      char name_h_artcc[31];
      char artcc_l_bndry[5];
      char name_l_artcc[31];
      /// GEOGRAPHIC POSITION DATA
      char lat[15];
      char lat_seconds[12];
      char lon[15];
      char lon_seconds[12];
      char accuracy[2];
      char lat_tacan[15];
      char lat_tacan_seconds[12];
      char lon_tacan[15];
      char lon_tacan_seconds[12];
      char elevation[7];
      char mag_var[6];
      char mag_epoch_yr[5];
      /// FACILITIES/FEATURES OF NAVAID
      char voice[4];
      char watts[5];
      char auto_voice_id[4];
      char mon_cat[2];
      char radio_call[31];
      char channel[5];
      char freq[7];
      char fan_id[25];
      char fan_type[11];
      char tr_bearng_fm[4];
      char prot_alt_freq[2];
      char lo_alt_use[4];
      char z_marker[4];
      char twx_bx_hrs[10];
      char twx_wx_ph[21];
      char fss_ident[5];
      char fss_name[31];
      char op_hrs[101];
      char notam_ident[5];
      /// CHARTING DATA
      char quad_id_rng_brg[17];
      /// NAVAID STATUS
      char nav_status[31];
      /// PITCH, CATCH AND SUA/ATCAA FLAGS
      char pitch_flg[2];
      char catch_flg[2];
      char sua_flg[2];
      char rest_flg[2];
      char hiwas_flg[2];
      char tweb_restrict[2];
    };

    struct ils6_record { /// REMARKS
      struct ils6_record * next_ils6;
      char lfsn[12];
      char rwy_end[4];
      char type[11];
      char remarks[351];
    };

    struct ils5_record { ///MARKER BEACON DATA
      struct ils5_record * next_ils5;
      char lfsn[12];
      char rwy_end[4];
      char type[11];
      char marker_type[3];
      char status[23];
      char eff_date[11];
      char lat_ant[15];
      char lat_ant_seconds[12];
      char lon_ant[15];
      char lon_ant_seconds[12];
      char lat_lon_code[3];
      char dist_frm_app_end[8];
      char dist_frm_rnwy_cl[5];
      char dir_of_ant_frm_rnwy[2];
      char src_dist_info[3];
      char elev[8];
      char fac_type[16];
      char loc_id[3];
      char name[31];
      char freq[4];
      char navaid_type[26];
      char low_ndb_status[23];
      char serv_provided[31];
    };

    struct ils4_record { ///DISTANCE MEASURING EQUIPMENT (DME) DATA
      char lfsn[12];
      char rwy_end[4];
      char type[11];
      char status[23];
      char eff_date[11];
      char lat_ant[15];
      char lat_ant_seconds[12];
      char lon_ant[15];
      char lon_ant_seconds[12];
      char lat_lon_code[3];
      char dist_frm_app_end[8];
      char dist_frm_rnwy_cl[5];
      char dir_of_ant_frm_rnwy[2];
      char src_dist_info[3];
      char elev[8];
      char channel[5];
      char dist_frm_stop[8];
    };

    struct ils3_record { ///GLIDE SLOPE DATA
      char lfsn[12];
      char rwy_end[4];
      char type[11];
      char status[23];
      char eff_date[11];
      char lat_ant[15];
      char lat_ant_seconds[12];
      char lon_ant[15];
      char lon_ant_seconds[12];
      char lat_lon_code[3];
      char dist_frm_app_end[8];
      char dist_frm_rnwy_cl[5];
      char dir_of_ant_frm_rnwy[2];
      char src_dist_info[3];
      char elev[8];
      char gsclass[16];
      char angle[6];
      char freq[8];
      char adj_elev[9];
    };

    struct ils2_record {  /// LOCALIZER DATA
      char lfsn[12];
      char rwy_end[4];
      char type[11];
      char status[23];
      char eff_date[11];
      char lat_ant[15];
      char lat_ant_seconds[12];
      char lon_ant[15];
      char lon_ant_seconds[12];
      char lat_lon_code[3];
      char dist_frm_app_end[8];
      char dist_frm_rnwy_cl[5];
      char dir_of_ant_frm_rnwy[2];
      char src_dist_info[3];
      char elev[8];
      char freq_mhz[8];
      char back_crs_status[16];
      char course_width[6];
      char width_at_threshold[8];
      char dist_from_stop[8];
      char dir_from_stop[2];
      char serv_code[3];
    };

    struct ils1_record {
      struct ils1_record * next_ils1;
      struct ils2_record * ils2;
      struct ils3_record * ils3;
      struct ils4_record * ils4;
      struct ils5_record * ils5_list;
      struct ils6_record * ils6_list;
      /// ILS AIRPORT/RUNWAY INFORMATION
      char lfsn[12];
      char rwy_end[4];
      char type[11];
      char id_code[7];
      char eff_date[11];
      char apt_name[51];
      char city[41];
      char st[3];
      char state_name[21];
      char faa_reg[4];
      char apt_id[5];
      char length[6];
      char width[5];
      /// ILS SYSTEM INFORMATION
      char cat[10];
      char own_name[51];
      char fac_oper[51];
      char app_bearing_mag[7];
      char mag_var[4];
    };

    struct awos2_record {
      struct awos2_record * next_awos2;

      char wx_sensor_ident[5];
      char wx_sensor_type[11];
      char remarks[237];
    };

    struct awos1_record {
      struct awos1_record * next_awos1;
      struct awos2_record * awos2_list;

      char wx_sensor_ident[5];
      char wx_sensor_type[11];
      char commisioning_status[2];
      char commisioning_date[11];
      char navaid_flag[2];
      char lat[15];
      char lon[16];
      char elevation[8];
      char survey_method[2];
      char frequency[8];
      char frequency2[8];
      char phone[15];
      char phone2[15];
      char lfsn[12];
      char city[41];
      char st[3];
      char info_eff_date[11];
    };

    struct twr9_record { /// ATIS may be one or more
      twr9_record * next_twr9;
      char ident[5];
      char sn[5];
      char hours[201];
      char purpose[101];
      char phone[19];
    };

    struct twr8_record { /// info on Class B-C-D-E airspace and airspace hours Only if Y to a class my be 0 or 1 record
 //   twr8_record * next_twr8;
      char ident[5];
      char class_b[2];
      char class_c[2];
      char class_d[2];
      char class_e[2];
      char hours[301];
    };

    struct twr7_record { /// general descriptive location and operations of Satellite Airport, one per each freq serviced by Master
      twr7_record * next_twr7;
      char ident[5];
      char sat_freq[45];
      char sat_use[51];
      char apt_site_nbr[12];
      char apt_id[5];
      char faa_reg[4];
      char st_name[31];
      char st[3];
      char city[41];
      char arpt_name[51];
      char lat[15];
      char lat_seconds[12];
      char lon[15];
      char lon_seconds[12];
      char fss_id[5];
      char fss_name[31];
      /// Master Airport Information
      char m_arpt_id[12];
      char m_faa_reg[4];
      char m_st_name[31];
      char m_st[3];
      char m_city[41];
      char m_arpt_name[51];
      char m_sat_freq[61];
    };

    struct twr6_record { /// textual remarks (may be NULL)
      twr6_record * next_twr6;
      char ident[5];
      char elem_nbr[6];
      char remark[801];
    };

    struct twr5_record { ///radar information  be null or one record
      char ident[5];
      char p_apr_call[10];
      char s_app_call[10];
      char p_dpt_call[10];
      char s_dpt_call[10];
      typedef char radar_line[11];
      radar_line radar_type[4];
      typedef char hours_line[201];
      hours_line radar_hrs[201][4];
};

    struct twr4_record { /// Services provide by master airpot to satellite airport (may be null)
      twr4_record * next_twr4;
      char ident[5];
      char service[101];
    };

    struct twr3_record { /// comm frequences (may be null) you know CRM 114 device :)
      twr3_record * next_twr3;
      char ident[5];
      typedef char freqline[45];
      freqline freq[45][9];
      typedef char useline[51];
      useline use[9];
      typedef char truncline[61];
      truncline freq_not_trunc[9];
    };

    struct twr2_record { /// description of the operating hours of the facility (may be null)
      char ident[5];
      char pmsv[201];
      char macp[201];
      char dyly[201];
      char p_app[201];
      char s_app[201];
      char p_dep[201];
      char s_dep[201];
      char twr[201];
    };

    struct twr1_record { /// general descriptive location and operation information
      twr1_record * next_twr1;
      twr2_record * twr2;
      twr3_record * twr3_list;
      twr4_record * twr4_list;
      twr5_record * twr5;
      twr6_record * twr6_list;
      twr7_record * twr7_list;
      twr8_record * twr8;
      twr9_record * twr9_list;
      char term_com_fac_id[5];
      char info_effect_date[11];
      /// Landing Facility(Airport) Data
      char lfsn[12];     //  (indext to airport)
      char faa_reg_code[4];
      char assoc_st_name[31];
      char assoc_st[3];
      char assoc_city_name[31];
      char offic_apt_name[51];
      char latitude[15];
      char latitude_seconds[12];
      char longitude[15];
      char longitude_seconds[12];
      char tie_in_fss[5];
      char tie_in_fss_name[31];
      /// Terminal Communications Facility Data
      char fac_type[13];
      char num_hours[3];
      char num_hours_code[4];
      char master_apt_id[5];
      char master_apt_name[51];
      char dir_find_eq[16];
      /// Terminal Communications Facility Off Airport
      char assoc_land_fac[51];
      char accoc_city[41];
      char st_prov[21];
      char st_county[26];
      char country_st[3];
      char faa_reg_code_off_apt[4];
      /// latitude/longitude data
         /// airport surveillance radar
      char as_rad_lat[15];
      char as_rad_lat_seconds[12];
      char as_rad_lon[15];
      char as_rad_lon_seconds[12];
         /// direction finding antenna
      char dfa_rad_lat[15];
      char dfa_rad_lat_seconds[12];
      char dfa_rad_lon[15];
      char dfa_rad_lon_seconds[12];
      /// Operator Data
      char twr[41];
      char mil_ops_data[41];
      char p_app_cntrl[41];
      char s_app_cntrl[41];
      char p_dep_cntrl[41];
      char s_dep_cntrl[41];
      /// radio call data
      char pilot_to_twr[27];
      char mill_ops_call[27];
      char p_app_cntr_call[27];
      char p_take_over_cntrl_call[27];
      char p_dep_cntr[27];
      char d_take_over_dep_cntrl[27];
    };


    struct runway_record {
      runway_record * next_rwy;
      char rwlanding_facility_site_number[12];
      char rw_st[3];
      char runway_id[8];
      /// COMMON RUNWAY DATA
      char runway_length[6];
      char runway_width[5];
      char runway_surface_type_cond[13];
      char runway_surface_treatment[6];
      char runway_pcn[12];
      char runway_light_edge_intensity[6];
      /// BASE END INFORMATION
      char b_id[4];
      char b_true_alignment[4];
      char b_ils_type[11];
      ils1_record * b_ils1;
      char b_rh_traffic[2];
      char b_rwy_markings[6];
      char b_rwy_condition[2];
      /// BASE END GEOGRAPHIC DATA
      char b_latitude[16];
      char b_latitude_seconds[13];
      char b_longitude[16];
      char b_longitude_seconds[13];
      char b_elevation[8];
      char b_threshold_xheight[4];
      char b_glide_slope[5];
      char b_dt_latitude[16];
      char b_dt_latitude_seconds[13];
      char b_dt_longitude[16];
      char b_dt_longitude_seconds[13];
      char b_dt_elevation[8];
      char b_dt_length[5];
      char b_dt_elev_at_td[8];
      /// BASE END LIGHTING DATA
      char b_glide_slope_ind[6];
      char b_rvr[4];
      char b_rvv[2];
      char b_approach_lights[9];
      char b_reil[2];
      char b_ctr_ln_lights[2];
      char b_td_lights[2];
      /// BASE END OBJECT DATA
      char b_object[12];
      char b_marked_lighted[5];
      char b_faa_cfr_77[6];
      char b_clearance_slope[3];
      char b_height_above_rwy[6];
      char b_dist_from_rwy[6];
      char b_center_line_offset[8];
      /// RECIPROCAL END INFORMATION
      char r_id[4];
      char r_true_alignment[4];
      char r_ils_type[11];
      ils1_record * r_ils1;
      char r_rh_traffic[2];
      char r_rwy_markings[6];
      char r_rwy_condition[2];
      /// RECIPROCAL END GEOGRAPHIC DATA
      char r_latitude[16];
      char r_latitude_seconds[13];
      char r_longitude[16];
      char r_longitude_seconds[13];
      char r_elevation[8];
      char r_threshold_xheight[4];
      char r_glide_slope[5];
      char r_dt_latitude[16];
      char r_dt_latitude_seconds[13];
      char r_dt_longitude[16];
      char r_dt_longitude_seconds[13];
      char r_dt_elevation[8];
      char r_dt_length[5];
      char r_dt_elev_at_td[8];
      /// RECIPROCAL END LIGHTING DATA
      char r_glide_slope_ind[6];
      char r_rvr[4];
      char r_rvv[1];
      char r_approach_lights[9];
      char r_reil[2];
      char r_ctr_ln_lights[2];
      char r_td_lights[2];
      /// RECIPROCAL END OBJECT DATA
      char r_object[12];
      char r_marked_lighted[5];
      char r_faa_cfr_77[6];
      char r_clearance_slope[3];
      char r_height_above_rwy[6];
      char r_dist_from_rwy[6];
      char r_center_line_offset[8];
      ///ADDITIONAL COMMON RUNWAY DATA
      char length_src[17];
      char length_date[11];
      char single_wheel_cap[7];
      char dual_wheel_cap[7];
      char dual_wheel_tandem_cap[7];
      char two_duel_wheel_tandem_cap[7];
      /// ADDITIONAL BASE END DATA
      char b_runway_end_gradient[6];
      char b_runway_end_gradient_dir[5];
      char b_runway_end_pos_src[17];
      char b_runway_end_pos_date[11];
      char b_runway_end_elev_src[17];
      char b_runway_end_elev_src_date[11];
      char b_dt_pos_src[17];
      char b_dt_pos_src_date[11];
      char b_dt_elev_src[17];
      char b_dt_elev_src_date[11];
      char b_td_elev_src[17];
      char b_td_elev_src_date[11];
      char b_tora[6];
      char b_toda[6];
      char b_asda[6];
      char b_lda[6];
      char b_lahso[6];
      char b_id_int_rw[8];
      char b_id_desc_ent[41];
      char b_lat_lahso[16];
      char b_lat_lahso_seconds[13];
      char b_lon_lahso[16];
      char b_lon_lahso_seconds[13];
      char b_latlon_lahso_src[17];
      char b_latlon_lahso_src_date[11];
      /// ADDITIONAL RECIPROCAL END DATA
      char r_runway_end_gradient[6];
      char r_runway_end_gradient_dir[5];
      char r_runway_end_pos_src[17];
      char r_runway_end_pos_date[11];
      char r_runway_end_elev_src[17];
      char r_runway_end_elev_src_date[11];
      char r_dt_pos_src[17];
      char r_dt_pos_src_date[11];
      char r_dt_elev_src[17];
      char r_dt_elev_src_date[11];
      char r_td_elev_src[17];
      char r_td_elev_src_date[11];
      char r_tora[6];
      char r_toda[6];
      char r_asda[6];
      char r_lda[6];
      char r_lahso[6];
      char r_id_int_rw[8];
      char r_id_desc_ent[41];
      char r_lat_lahso[16];
      char r_lat_lahso_seconds[13];
      char r_lon_lahso[16];
      char r_lon_lahso_seconds[13];
      char r_latlon_lahso_src[17];
      char r_latlon_lahso_src_date[11];

    };

    struct airport_rmk_record {
      struct airport_rmk_record * next_apt_rmk;
      char rmk_lfsn[12];
      char rmk_lfst[3];
      char rmk_name[14];
      char rmk_text[1501];
    };

    struct airport_ars_record {
      struct airport_ars_record * next_apt_ars;
      char ars_lfsn[12];
      char ars_lfst[3];
      char ars_runway[8];
      char ars_runway_end[4];
      char ars_type[10];
    };

    struct airport_att_record {
       airport_att_record * next_apt_att;
       char att_lfsn[12];
       char att_st[3];
       char att_sn[3];
       char att_sched[109];
    };


    struct airport_ils_record {
      struct airport_ils_record * next_apt_ils;
      struct ils1_record * apt_ils1;
    };

    struct airport_record {
      airport_record * next_apt;
      airport_att_record * att_list;
      runway_record  * rwy_list;
      airport_ars_record * ars_list;
      airport_rmk_record * rmk_list;

      twr1_record * twr1;
      awos1_record * awos1;
      airport_ils_record * ils_list;

      char landing_facility_site_number[12];
      char landing_facility_index[12];
      char landing_facility_type[14];
      char location_identifier[5];
      char information_effective_date[11];
      /// DEMOGRAPHIC DATA
      char faa_region_code[4];
      char faa_district_office[5];
      char st[3];
      char stname[21];
      char county[22];
      char county_st[3];
      char city[41];
      char name[51];
      /// OWNERSHIP DATA
      char ownership_type[3];
      char facility_use[3];
      char own_name[36];
      char own_addr[73];
      char own_city[46];
      char own_phone[17];
      char mgr_name[36];
      char mgr_addr[73];
      char mgr_city[46];
      char mgr_phone[17];
      /// GEOGRAPHIC DATA
      char airport_latitude_formatted[16];
      char airport_latitude_seconds[13];
      char airport_longitude_formatted[16];
      char airport_longitude_seconds[13];
      char airport_ref_determ_method[2];
      char airport_elevation[8];
      char airport_elevation_method[2];
      char airport_mag_var[4];
      char airport_mag_var_epoch_yr[5];
      char traffic_pattern_altitude[5];
      char section_chart[31];
      char dist_from_business[3];
      char dir_from_business[4];
      char land_area[6];
      /// FAA SERVICES
      char boundary_artcc[5];
      char boundary_artcc_faa[4];
      char boundary_artcc_name[31];
      char resp_artcc_rep_id[5];
      char resp_artcc_faa[4];
      char resp_artcc_name[31];
      char tie_in_phys[2];
      char tie_in_id[5];
      char tie_in_name[31];
      char local_phone[17];
      char toll_free_phone[17];
      char alt_fss_id[5];
      char alt_fss_name[31];
      char alt_fss_toll_free[17];
      char notam_id[5];
      char notam_available[2];
      /// FEDERAL STATUS
      char airport_activ_data[8];
      char airport_status_code[3];
      char airport_arf_cert[16];
      char NPIAS_FEDERAL_code[8];
      char airport_airspace_analysis[14];
      char airport_customs_poe[2];
      char airport_customs_landing[2];
      char military_civil_joint_use[2];
      char military_landing_rights[2];
      ///AIRPORT INSPECTION DATA
      char airport_insp_method[3];
      char airport_insp_agency[2];
      char airport_last_inspect[9];
      char airport_last_info_req[9];
      /// AIRPORT SERVICES
      char fuel_types[41];
      char airframe_repair[6];
      char powerplant_repair[6];
      char bottled_oxy[9];
      char bulk_oxy[9];
      /// AIRPORT FACILITIES
      char light_sched[8];
      char beacon_light_sched[8];
      char airport_has_tower[2];
      char unicom[8];
      char ctaf[8];
      char segment_circle_marker[5];
      char lens_color[4];
      char landing_fee[2];
      char medical_use[2];
      /// BASED AIRCRAFT
      char sega[4];
      char mega[4];
      char jetga[4];
      char gaheli[4];
      char glider[4];
      char military[4];
      char ultralight[4];
      /// ANNUAL OPERATIONS
      char cab_carriers[7];
      char commuter[7];
      char air_taxi[7];
      char ga_ops[7];
      char ga_itinerant[7];
      char mil_ops[7];
      char ending_date[11];
      /// ADDITIONAL AIRPORT DATA
      char pos_source[17];
      char pos_source_date[11];
      char apt_elev_source[17];
      char apt_elev_source_date[11];
      char contract_fuel[2];
      char transient_store[13];
      char other_ac_services[71];
      char wind_indicator[4];
      char airport_official_icao[8];
      char min_op_network[2];
    };

//  std::string Airport_Models_path;

  std::string Airport_sign_base_path;
  std::string Short_Airport_sign_base_path;
  std::string Airport_sign_path;
  std::string Short_Airport_sign_path;

  std::string Nav_sign_base_path;
  std::string Short_Nav_sign_base_path;
  std::string Nav_sign_path;
  std::string Short_Nav_sign_path;


  std::string Objects_base_path;

  char NASRairportbuffer[2000];  /// always check sizing when records change format
                                 /// TWR2 1410+200 currently
  void process_airport_record();
  void process_attendance_record();
  void process_runway_record();
  void process_arrest_record();
  void process_remark_record();

  void process_twr1_record();
  void process_twr2_record();
  void process_twr3_record();
  void process_twr4_record();
  void process_twr5_record();
  void process_twr6_record();
  void process_twr7_record();
  void process_twr8_record();
  void process_twr9_record();

  void process_awos1_record();
  void process_awos2_record();

  void process_ils1_record();
  void process_ils2_record();
  void process_ils3_record();
  void process_ils4_record();
  void process_ils5_record();
  void process_ils6_record();

  void process_fix1_record();
  void process_fix2_record();
  void process_fix3_record();
  void process_fix4_record();
  void process_fix5_record();

  void process_nav1_record();
  void process_nav2_record();
  void process_nav3_record();
  void process_nav4_record();
  void process_nav5_record();
  void process_nav6_record();

/// AIRPORT RECORDS
    airport_record * head_apt;
    airport_record * current_apt;
    airport_record * last_apt;
/// ILS
    airport_ils_record * current_apt_ils;
    airport_ils_record * current_ils_list;
/// ATT (ATTENDANCE)
    airport_att_record * current_att;
    airport_att_record * head_att;
    airport_att_record * last_att;
/// ARS (ARRESTING GEAR SYSTEMS)
    airport_ars_record * current_ars;
    airport_ars_record * head_ars;
    airport_ars_record * last_ars;
/// RUNWAY RECORDS
    runway_record  * current_rwy;
    runway_record  * head_rwy;
    runway_record  * last_rwy;
/// RMK (AIRPORT REMARKS)
    airport_rmk_record * current_rmk;
    airport_rmk_record * head_rmk;
    airport_rmk_record * last_rmk;

/// tower records
    twr1_record * head_twr1;
    twr1_record * current_twr1;
    twr1_record * last_twr1;

    twr2_record * twr2;

    twr3_record * head_twr3;
    twr3_record * current_twr3;
    twr3_record * last_twr3;

    twr4_record * head_twr4;
    twr4_record * current_twr4;
    twr4_record * last_twr4;

    twr5_record * twr5;

    twr6_record * head_twr6;
    twr6_record * current_twr6;
    twr6_record * last_twr6;

    twr7_record * head_twr7;
    twr7_record * current_twr7;
    twr7_record * last_twr7;

    twr8_record * twr8;

    twr9_record * head_twr9;
    twr9_record * current_twr9;
    twr9_record * last_twr9;

/// awos records
    awos1_record *head_awos1;
    awos1_record *current_awos1;
    awos1_record *last_awos1;

    awos2_record *head_awos2;
    awos2_record *current_awos2;
    awos2_record *last_awos2;


/// ILS records
    ils1_record * head_ils1;
    ils1_record * current_ils1;
    ils1_record * last_ils1;

    ils2_record * ils2;

    ils3_record * ils3;

    ils4_record * ils4;

    ils5_record * head_ils5;
    ils5_record * current_ils5;
    ils5_record * last_ils5;

    ils6_record * head_ils6;
    ils6_record * current_ils6;
    ils6_record * last_ils6;

/// NAV RECORDS
    nav1_record * head_nav1;
    nav1_record * current_nav1;
    nav1_record * last_nav1;

    nav2_record * head_nav2;
    nav2_record * current_nav2;
    nav2_record * last_nav2;

    nav3_record * head_nav3;
    nav3_record * current_nav3;
    nav3_record * last_nav3;

    nav4_record * head_nav4;
    nav4_record * current_nav4;
    nav4_record * last_nav4;

    nav5_record * head_nav5;
    nav5_record * current_nav5;
    nav5_record * last_nav5;

    nav6_record * head_nav6;
    nav6_record * current_nav6;
    nav6_record * last_nav6;

/// FIX RECORDS
    fix1_record * head_fix1;
    fix1_record * current_fix1;
    fix1_record * last_fix1;

    fix2_record * head_fix2;
    fix2_record * current_fix2;
    fix2_record * last_fix2;

    fix3_record * head_fix3;
    fix3_record * current_fix3;
    fix3_record * last_fix3;

    fix4_record * head_fix4;
    fix4_record * current_fix4;
    fix4_record * last_fix4;

    fix5_record * head_fix5;
    fix5_record * current_fix5;
    fix5_record * last_fix5;

    struct avl_tree_node * head_avl_apt; /// AIRPORT ID INDEX
    struct avl_tree_node * head_avl_apt_lfsn; /// AIRPORT LANDING FACILITY SITE NUMBER (KEY INDEX IN NASR)

    void make_flightgear_path_addition(char * path);
    void generate_airport_sign();
    void generate_airport_sign(char * path);

    int n_apt;
    int n_airport_type;
    int n_rwy;

    std::string Airport     ;//  = "AIRPORT      ";  // this is the way they are in the APT.TXT padded with spaces
    std::string Balloonport ;//  = "BALLOONPORT  ";  // this is the way they are in the APT.TXT padded with spaces
    std::string Seaplanebase;//  = "SEAPLANE BASE";  // this is the way they are in the APT.TXT padded with spaces
    std::string Gliderport  ;//  = "GLIDERPORT   ";  // this is the way they are in the APT.TXT padded with spaces
    std::string Heliport    ;//  = "HELIPORT     ";  // this is the way they are in the APT.TXT padded with spaces
    std::string Ultralight  ;//  = "ULTRALIGHT   ";  // this is the way they are in the APT.TXT padded with spaces

    public:
      ///inline
      airport(void)
      {

      }
      airport(OpenEaglePaths * path_ptr)
      {
        paths = path_ptr;
        Airport_sign_base_path = "";
        Short_Airport_sign_base_path = "";
        Airport_sign_path = "";
        Short_Airport_sign_path = "";
        Objects_base_path = "";

        Airport       = "AIRPORT      ";  // this is the way they are in the APT.TXT padded with spaces
        Balloonport   = "BALLOONPORT  ";  // this is the way they are in the APT.TXT padded with spaces
        Seaplanebase  = "SEAPLANE BASE";  // this is the way they are in the APT.TXT padded with spaces
        Gliderport    = "GLIDERPORT   ";  // this is the way they are in the APT.TXT padded with spaces
        Heliport      = "HELIPORT     ";  // this is the way they are in the APT.TXT padded with spaces
        Ultralight    = "ULTRALIGHT   ";  // this is the way they are in the APT.TXT padded with spaces

        n_apt=0;
        n_airport_type = 0;
        n_rwy=0;

        head_apt    = NULL;
        current_apt = NULL;
        last_apt    = NULL;

        current_ils_list = NULL;


        current_att = NULL;
        head_att    = NULL;
        last_att    = NULL;

        current_ars = NULL;
        head_ars    = NULL;
        last_ars    = NULL;

        current_rwy = NULL;
        head_rwy    = NULL;
        last_rwy    = NULL;

        current_rmk = NULL;
        head_rmk    = NULL;
        last_rmk    = NULL;

    	head_twr1    = NULL;
        current_twr1 = NULL;
        last_twr1    = NULL;

        twr2         = NULL;

        head_twr3    = NULL;
        current_twr3 = NULL;
        last_twr3    = NULL;

        head_twr4    = NULL;
        current_twr4 = NULL;
        last_twr4    = NULL;

        twr5         = NULL;

        head_twr6    = NULL;
        current_twr6 = NULL;
        last_twr6    = NULL;

        head_twr7    = NULL;
        current_twr7 = NULL;
        last_twr7    = NULL;

        twr8         = NULL;

        head_twr9    = NULL;
        current_twr9 = NULL;
        last_twr9    = NULL;

        head_awos1    = NULL;
        current_awos1 = NULL;
        last_awos1    = NULL;

        head_awos2    = NULL;
        current_awos2 = NULL;
        last_awos2    = NULL;

        head_ils1     = NULL;
        current_ils1  = NULL;
        last_ils1     = NULL;

        ils2          = NULL;

        ils3          = NULL;

        ils4          = NULL;

        head_ils5     = NULL;
        head_ils5     = NULL;
        head_ils5     = NULL;

        head_ils6     = NULL;
        head_ils6     = NULL;
        head_ils6     = NULL;

        head_fix1     = NULL;
        current_fix1  = NULL;
        last_fix1     = NULL;

        head_fix2     = NULL;
        current_fix2  = NULL;
        last_fix2     = NULL;

        head_fix3     = NULL;
        current_fix3  = NULL;
        last_fix3     = NULL;

        head_fix4     = NULL;
        current_fix4  = NULL;
        last_fix4     = NULL;

        head_fix5     = NULL;
        current_fix5  = NULL;
        last_fix5     = NULL;

        head_nav1     = NULL;
        current_nav1  = NULL;
        last_nav1     = NULL;

        head_nav2     = NULL;
        current_nav2  = NULL;
        last_nav2     = NULL;

        head_nav3     = NULL;
        current_nav3  = NULL;
        last_nav3     = NULL;

        head_nav4     = NULL;
        current_nav4  = NULL;
        last_nav4     = NULL;

        head_nav5     = NULL;
        current_nav5  = NULL;
        last_nav5     = NULL;

        head_nav6     = NULL;
        current_nav6  = NULL;
        last_nav6     = NULL;

        head_avl_apt       = initialize_avl_tree();
        head_avl_apt_lfsn  = initialize_avl_tree();
        head_apt           = NULL;
      }
      inline ~airport(void)
      {
        printf("~airportz(void) entry\n");
        current_apt = head_apt;
        int i = 0;
        while (head_apt!=NULL) {
          i++;
          current_apt=head_apt;
          head_apt = head_apt->next_apt;
          head_rwy = current_apt->rwy_list;
          int j = 0;
          while (head_rwy!=NULL) {
            j++;
            current_rwy=head_rwy;
            head_rwy = head_rwy->next_rwy;
            free(current_rwy);
          }
          free( current_apt);
        }
        erase_avl_tree(head_avl_apt);
        erase_avl_tree(head_avl_apt_lfsn);
        printf("gave up avl_tree nodes\n");
        // exit(0);
      }
};
#endif
