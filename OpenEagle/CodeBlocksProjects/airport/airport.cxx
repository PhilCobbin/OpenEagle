/***************************************************************
 * Name:      airport.cxx
 * Purpose:   read, summarize, and generate files related to the
 * FAA apt.txt file et al, part of the NASR 56 day cycle database
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2021-04-11
 * Copyright: Philip Cobbin (cobbin.com)
 * License    GPLv3 see: https://www.gnu.org/licenses/gpl-3.0.html
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 **************************************************************/
#include <string.h>
#include <string>
#include "airport.hxx"
#include <stdio.h>
#include <cstddef>
#include "../read_data/read_data.hxx"
#include "../data_conversion/data_conversion.hxx"
#include "../OpenEaglePaths/OpenEaglePaths.hxx"
#include "../tile/tile.hxx"
#include "../time/time.hxx"
#include "../TimeStrings/TimeStrings.hxx"
//#include "../avl_tree/avl_tree.hxx"
void airport::set_terminal_io(bool do_terminal_io)
{
  terminal_io = do_terminal_io;
}

bool airport::lookup_airport_elevation(char * apt,double *elevation)
{
  struct avl_tree_node *avl_ptr = search_avl_tree (apt, false, head_avl_apt);
  if (avl_ptr == NULL) return false;
  *elevation = strtod((char *)avl_ptr->data_ptr,NULL);
  return true;
}

bool airport::lookup_airport_and_set_current(char * apt)
{
  struct avl_tree_node *avl_ptr = search_avl_tree (apt, false, head_avl_apt);
  if (avl_ptr == NULL) return false;
  current_apt = (airport_record *) avl_ptr->data_ptr;
  return true;
}
bool airport::lookup_airport_and_set_current_by_lfsn(char * lfsn)
{
  struct avl_tree_node *avl_ptr = search_avl_tree (lfsn, false, head_avl_apt_lfsn);
  if (avl_ptr == NULL) return false;
  current_apt = (airport_record *) avl_ptr->data_ptr;
  return true;
}

char * airport::get_airport_type()               {  return current_apt->landing_facility_type;}
char * airport::get_location_identifier()        {  return current_apt->location_identifier; }
char * airport::get_airport_effective_date()     {  return current_apt->information_effective_date; }
char * airport::get_faa_region_code()            {  return current_apt->faa_region_code;}
char * airport::get_faa_district_office()        {  return current_apt->faa_district_office;}
char * airport::get_st()                         {  return current_apt->st; }
char * airport::get_stname()                     {  return current_apt->stname; }
char * airport::get_county()                     {  return current_apt->county; }
char * airport::get_county_st()                  {  return current_apt->county_st;}
char * airport::get_city()                       {  return current_apt->city;}
char * airport::get_name()                       {  return current_apt->name;}
char * airport::get_ownership_type()             {  return current_apt->ownership_type; }
char * airport::get_facility_use()               {  return current_apt->facility_use;}
char * airport::get_own_name()                   {  return current_apt->own_name;}
char * airport::get_own_addr()                   {  return current_apt->own_addr;}
char * airport::get_own_city()                   {  return current_apt->own_city;}
char * airport::get_own_phone()                  {  return current_apt->own_phone;}
char * airport::get_mgr_name()                   {  return current_apt->mgr_name;}
char * airport::get_mgr_addr()                   {  return current_apt->mgr_addr;}
char * airport::get_mgr_city()                   {  return current_apt->mgr_city;}
char * airport::get_mgr_phone()                  {  return current_apt->mgr_phone;}
     /// GEOGRAPHIC DATA
char * airport::get_airport_latitude_formatted() {  return current_apt->airport_latitude_formatted;}
char * airport::get_airport_latitude_seconds()   {  return current_apt->airport_latitude_seconds;}
char * airport::get_airport_longitude_formatted(){  return current_apt->airport_longitude_formatted;}
char * airport::get_airport_longitude_seconds()  {  return current_apt->airport_longitude_seconds;}
char * airport::get_airport_ref_determ_method()  {  return current_apt->airport_ref_determ_method;}
char * airport::get_airport_elevation()          {  return current_apt->airport_elevation;}
char * airport::get_airport_elevation_method()   {  return current_apt->airport_elevation_method;}
char * airport::get_airport_mag_var()            {  return current_apt->airport_mag_var;}
char * airport::get_airport_mag_var_epoch_yr()   {  return current_apt->airport_mag_var_epoch_yr;}
char * airport::get_traffic_pattern_altitude()   {  return current_apt->traffic_pattern_altitude;}
char * airport::get_section_chart()              {  return current_apt->section_chart;}
char * airport::get_dist_from_business()         {  return current_apt->dist_from_business;}
char * airport::get_dir_from_business()          {  return current_apt->dir_from_business;}
char * airport::get_land_area()                  {  return current_apt->land_area;}
 /// FAA SERVICES
char * airport::get_boundary_artcc()             {  return current_apt->boundary_artcc;}
char * airport::get_boundary_artcc_faa()         {  return current_apt->boundary_artcc_faa;}
char * airport::get_boundary_artcc_name()        {  return current_apt->boundary_artcc_name;}
char * airport::get_resp_artcc_rep_id()          {  return current_apt->resp_artcc_rep_id;}
char * airport::get_resp_artcc_faa()             {  return current_apt->resp_artcc_faa;}
char * airport::get_resp_artcc_name()            {  return current_apt->resp_artcc_name;}
char * airport::get_tie_in_phys()                {  return current_apt->tie_in_phys;}
char * airport::get_tie_in_id()                  {  return current_apt->tie_in_id;}
char * airport::get_tie_in_name()                {  return current_apt->tie_in_name;}
char * airport::get_local_phone()                {  return current_apt->local_phone;}
char * airport::get_toll_free_phone()            {  return current_apt->toll_free_phone;}
char * airport::get_alt_fss_id()                 {  return current_apt->alt_fss_id;}
char * airport::get_alt_fss_name()               {  return current_apt->alt_fss_name;}
char * airport::get_alt_fss_toll_free()          {  return current_apt->alt_fss_toll_free;}
char * airport::get_notam_id()                   {  return current_apt->notam_id;}
char * airport::get_notam_available()            {  return current_apt->notam_available;}
/// FEDERAL STATUS
char * airport::get_airport_activ_data()         {  return current_apt->airport_activ_data; }
char * airport::get_airport_status_code()        {  return current_apt->airport_status_code; }
char * airport::get_airport_arf_cert()           {  return current_apt->airport_arf_cert; }
char * airport::get_NPIAS_FEDERAL_code()         {  return current_apt->NPIAS_FEDERAL_code; }
char * airport::get_airport_airspace_analysis()  {  return current_apt->airport_airspace_analysis;}
char * airport::get_airport_customs_poe()        {  return current_apt->airport_customs_poe; }
char * airport::get_airport_customs_landing()    {  return current_apt->airport_customs_landing;}
char * airport::get_military_civil_joint_use()   {  return current_apt->military_civil_joint_use;}
char * airport::get_military_landing_rights()    {  return current_apt->military_landing_rights;}
///AIRPORT INSPECTION DATA
char * airport::get_airport_insp_method()        {  return current_apt->airport_insp_method;}
char * airport::get_airport_insp_agency()        {  return current_apt->airport_insp_agency;}
char * airport::get_airport_last_inspect()       {  return current_apt->airport_last_inspect;}
char * airport::get_airport_last_info_req()      {  return current_apt->airport_last_info_req;}
/// AIRPORT SERVICES
char * airport::get_fuel_types()                 {  return current_apt->fuel_types;}
char * airport::get_airframe_repair()            {  return current_apt->airframe_repair;}
char * airport::get_powerplant_repair()          {  return current_apt->powerplant_repair;}
char * airport::get_bottled_oxy()                {  return current_apt->bottled_oxy;}
char * airport::get_bulk_oxy()                   {  return current_apt->bulk_oxy;}
/// AIRPORT FACILITIES
char * airport::get_light_sched()                {  return current_apt->light_sched;}
char * airport::get_beacon_light_sched()         {  return current_apt->beacon_light_sched;}
char * airport::get_airport_has_tower()          {  return current_apt->airport_has_tower;}
char * airport::get_unicom()                     {  return current_apt->unicom;}
char * airport::get_ctaf()                       {  return current_apt->ctaf;}
char * airport::get_segment_circle_marker()      {  return current_apt->segment_circle_marker;}
char * airport::get_lens_color()                 {  return current_apt->lens_color;}
char * airport::get_landing_fee()                {  return current_apt->landing_fee;}
char * airport::get_medical_use()                {  return current_apt->medical_use;}
/// BASED AIRCRAFT
char * airport::get_sega()                       {  return current_apt->sega;}
char * airport::get_mega()                       {  return current_apt->mega;}
char * airport::get_jetga()                      {  return current_apt->jetga;}
char * airport::get_gaheli()                     {  return current_apt->gaheli;}
char * airport::get_glider()                     {  return current_apt->glider;}
char * airport::get_military()                   {  return current_apt->military;}
char * airport::get_ultralight()                 {  return current_apt->ultralight;}
/// ANNUAL OPERATIONS
char * airport::get_cab_carriers()               {  return current_apt->cab_carriers;}
char * airport::get_commuter()                   {  return current_apt->commuter;}
char * airport::get_air_taxi()                   {  return current_apt->air_taxi;}
char * airport::get_ga_ops()                     {  return current_apt->ga_ops;}
char * airport::get_ga_itinerant()               {  return current_apt->ga_itinerant;}
char * airport::get_mil_ops()                    {  return current_apt->mil_ops;}
char * airport::get_ending_date()                {  return current_apt->ending_date;}
/// ADDITIONAL AIRPORT DATA
char * airport::get_pos_source()                 {  return current_apt->pos_source;}
char * airport::get_pos_source_date()            {  return current_apt->pos_source_date;}
char * airport::get_apt_elev_source()            {  return current_apt->apt_elev_source;}
char * airport::get_apt_elev_source_date()       {  return current_apt->apt_elev_source_date;}
char * airport::get_contract_fuel()              {  return current_apt->contract_fuel;}
char * airport::get_transient_store()            {  return current_apt->transient_store;}
char * airport::get_other_ac_services()          {  return current_apt->other_ac_services;}
char * airport::get_wind_indicator()             {  return current_apt->wind_indicator;}
char * airport::get_airport_official_icao()      {  return current_apt->airport_official_icao;}
char * airport::get_min_op_network()             {  return current_apt->min_op_network; }

bool airport::have_attendance_records()          {  current_att =  current_apt->att_list;  if (current_att != NULL) return true; else return false;}
bool airport::next_attendance_record()           {  if (current_att->next_apt_att != NULL) {    current_att = current_att->next_apt_att;    return true;  }  else return false;}
char * airport::get_att_lfsn()                   {  return current_att->att_lfsn;}
char * airport::get_att_st()                     {  return current_att->att_st;}
char * airport::get_att_sn()                     {  return current_att->att_sn;}
char * airport::get_att_sched()                  {  return current_att->att_sched;}

bool airport::have_arrest_records()              {  current_ars =  current_apt->ars_list;  if (current_ars != NULL) return true; else return false;}
bool airport::next_arrest_record()               {  if (current_ars->next_apt_ars != NULL) { current_ars = current_ars->next_apt_ars; return true; }  else return false; }
char * airport::get_ars_lfsn()                   {  return current_ars->ars_lfsn;}
char * airport::get_ars_lfst()                   {  return current_ars->ars_lfst;}
char * airport::get_ars_runway()                 {  return current_ars->ars_runway;}
char * airport::get_ars_runway_end()             {  return current_ars->ars_runway_end;}
char * airport::get_ars_type()                   {  return current_ars->ars_type;}

bool airport::have_remark_records()              { current_rmk = current_apt->rmk_list;  if (current_rmk != NULL) return true; else return false;}
bool airport::next_remark_record()               { if (current_rmk->next_apt_rmk != NULL) { current_rmk = current_rmk->next_apt_rmk; return true; }  else return false;}
char * airport::get_rmk_lfsn()                   {  return current_rmk->rmk_lfsn;}
char * airport::get_rmk_lfst()                   {  return current_rmk->rmk_lfst;}
char * airport::get_rmk_name()                   {  return current_rmk->rmk_name;}
char * airport::get_rmk_text()                   {  return current_rmk->rmk_text;}

/// runway records
bool airport::have_runway_records()              { current_rwy =  current_apt->rwy_list; if (current_rwy != NULL) return true; else return false;}
bool airport::next_runway_record()               { if (current_rwy->next_rwy != NULL) { current_rwy = current_rwy->next_rwy; return true;}  else return false;}
char * airport::get_rwlanding_facility_site_number(){  return current_rwy->rwlanding_facility_site_number;}
char * airport::get_rw_st()                      {  return current_rwy->rw_st;}
char * airport::get_runway_id()                  {  return current_rwy->runway_id;}
/// COMMON RUNWAY DATA
char * airport::get_runway_length()              {  return current_rwy->runway_length;}
char * airport::get_runway_width()               {  return current_rwy->runway_width;}
char * airport::get_runway_surface_type_cond()   {  return current_rwy->runway_surface_type_cond;}
char * airport::get_runway_surface_treatment()   {  return current_rwy->runway_surface_treatment;}
char * airport::get_runway_pcn()                 {  return current_rwy->runway_pcn;}
char * airport::get_runway_light_edge_intensity(){  return current_rwy->runway_light_edge_intensity;}
/// BASE END INFORMATION
char * airport::get_b_id()                       {  return current_rwy->b_id;}
char * airport::get_b_true_alignment()           {  return current_rwy->b_true_alignment;}
char * airport::get_b_ils_type()                 {  return current_rwy->b_ils_type; }
char * airport::get_b_rh_traffic()               {  return current_rwy->b_rh_traffic;}
char * airport::get_b_rwy_markings()             {  return current_rwy->b_rwy_markings;}
char * airport::get_b_rwy_condition()            {  return current_rwy->b_rwy_condition;}
/// BASE END GEOGRAPHIC DATA
char * airport::get_b_latitude()                 {  return current_rwy->b_latitude;}
char * airport::get_b_latitude_seconds()         {  return current_rwy->b_latitude_seconds;}
char * airport::get_b_longitude()                {  return current_rwy->b_longitude;}
char * airport::get_b_longitude_seconds()        {  return current_rwy->b_longitude_seconds;}
char * airport::get_b_elevation()                {  return current_rwy->b_elevation;}
char * airport::get_b_threshold_xheight()        {  return current_rwy->b_threshold_xheight;}
char * airport::get_b_glide_slope()              {  return current_rwy->b_glide_slope;}
char * airport::get_b_dt_latitude()              {  return current_rwy->b_dt_latitude;}
char * airport::get_b_dt_latitude_seconds()      {  return current_rwy->b_dt_latitude_seconds;}
char * airport::get_b_dt_longitude()             {  return current_rwy->b_dt_latitude_seconds;}
char * airport::get_b_dt_longitude_seconds()     {  return current_rwy->b_dt_longitude_seconds;}
char * airport::get_b_dt_elevation()             {  return current_rwy->b_dt_elevation;}
char * airport::get_b_dt_length()                {  return current_rwy->b_dt_length;}
char * airport::get_b_dt_elev_at_td()            {  return current_rwy->b_dt_elev_at_td;}
/// BASE END LIGHTING DATA
char * airport::get_b_glide_slope_ind()          {  return current_rwy->b_glide_slope_ind;}
char * airport::get_b_rvr()                      {  return current_rwy->b_rvr;}
char * airport::get_b_rvv()                      {  return current_rwy->b_rvv;}
char * airport::get_b_approach_lights()          {  return current_rwy->b_approach_lights;}
char * airport::get_b_reil()                     {  return current_rwy->b_reil;}
char * airport::get_b_ctr_ln_lights()            {  return current_rwy->b_ctr_ln_lights;}
char * airport::get_b_td_lights()                {  return current_rwy->b_td_lights;}
/// BASE END OBJECT DATA
char * airport::get_b_object()                   {  return current_rwy->b_object;}
char * airport::get_b_marked_lighted()           {  return current_rwy->b_marked_lighted;}
char * airport::get_b_faa_cfr_77()               {  return current_rwy->b_faa_cfr_77;}
char * airport::get_b_clearance_slope()          {  return current_rwy->b_clearance_slope;}
char * airport::get_b_height_above_rwy()         {  return current_rwy->b_height_above_rwy;}
char * airport::get_b_dist_from_rwy()            {  return current_rwy->b_dist_from_rwy;}
char * airport::get_b_center_line_offset()       {  return current_rwy->b_center_line_offset;}
/// RECIPROCAL END INFORMATION
char * airport::get_r_id()                       {  return current_rwy->r_id;}
char * airport::get_r_true_alignment()           {  return current_rwy->r_true_alignment;}
char * airport::get_r_ils_type()                 {  return current_rwy->r_ils_type;}
char * airport::get_r_rh_traffic()               {  return current_rwy->r_rh_traffic;}
char * airport::get_r_rwy_markings()             {  return current_rwy->r_rwy_markings;}
char * airport::get_r_rwy_condition()            {  return current_rwy->r_rwy_condition;}
/// RECIPROCAL END GEOGRAPHIC DATA
char * airport::get_r_latitude()                 {  return current_rwy->r_latitude;}
char * airport::get_r_latitude_seconds()         {  return current_rwy->r_latitude_seconds;}
char * airport::get_r_longitude()                {  return current_rwy->r_longitude;}
char * airport::get_r_longitude_seconds()        {  return current_rwy->r_longitude_seconds;}
char * airport::get_r_elevation()                {  return current_rwy->r_elevation;}
char * airport::get_r_threshold_xheight()        {  return current_rwy->r_threshold_xheight;}
char * airport::get_r_glide_slope()              {  return current_rwy->r_glide_slope;}
char * airport::get_r_dt_latitude()              {  return current_rwy->r_dt_latitude;}
char * airport::get_r_dt_latitude_seconds()      {  return current_rwy->r_dt_latitude_seconds;}
char * airport::get_r_dt_longitude()             {  return current_rwy->r_dt_longitude;}
char * airport::get_r_dt_longitude_seconds()     {  return current_rwy->r_dt_longitude_seconds;}
char * airport::get_r_dt_elevation()             {  return current_rwy->r_dt_elevation;}
char * airport::get_r_dt_length()                {  return current_rwy->r_dt_length;}
char * airport::get_r_dt_elev_at_td()            {  return current_rwy->r_dt_elev_at_td;}
/// RECIPROCAL END LIGHTING DATA
char * airport::get_r_glide_slope_ind()          {  return current_rwy->r_glide_slope_ind;}
char * airport::get_r_rvr()                      {  return current_rwy->r_rvr;}
char * airport::get_r_rvv()                      {  return current_rwy->r_rvv;}
char * airport::get_r_approach_lights()          {  return current_rwy->r_approach_lights;}
char * airport::get_r_reil()                     {  return current_rwy->r_reil;}
char * airport::get_r_ctr_ln_lights()            {  return current_rwy->r_ctr_ln_lights;}
char * airport::get_r_td_lights()                {  return current_rwy->r_td_lights;}
/// RECIPROCAL END OBJECT DATA
char * airport::get_r_object()                   {  return current_rwy->r_object;}
char * airport::get_r_marked_lighted()           {  return current_rwy->r_marked_lighted;}
char * airport::get_r_faa_cfr_77()               {  return current_rwy->r_faa_cfr_77;}
char * airport::get_r_clearance_slope()          {  return current_rwy->r_clearance_slope;}
char * airport::get_r_height_above_rwy()         {  return current_rwy->r_height_above_rwy;}
char * airport::get_r_dist_from_rwy()            {  return current_rwy->r_dist_from_rwy; }
char * airport::get_r_center_line_offset()       {  return current_rwy->r_center_line_offset;}
///ADDITIONAL COMMON RUNWAY DATA
char * airport::get_length_src()                 {  return current_rwy->length_src;}
char * airport::get_length_date()                {  return current_rwy->length_date;}
char * airport::get_single_wheel_cap()           {  return current_rwy->single_wheel_cap;}
char * airport::get_dual_wheel_cap()             {  return current_rwy->dual_wheel_cap;}
char * airport::get_dual_wheel_tandem_cap()      {  return current_rwy->dual_wheel_tandem_cap;}
char * airport::get_two_duel_wheel_tandem_cap()  {  return current_rwy->two_duel_wheel_tandem_cap;}
/// ADDITIONAL BASE END DATA
char * airport::get_b_runway_end_gradient()      {  return current_rwy->b_runway_end_gradient;}
char * airport::get_b_runway_end_gradient_dir()  {  return current_rwy->b_runway_end_gradient_dir;}
char * airport::get_b_runway_end_pos_src()       {  return current_rwy->b_runway_end_pos_src;}
char * airport::get_b_runway_end_pos_date()      {  return current_rwy->b_runway_end_pos_date;}
char * airport::get_b_runway_end_elev_src()      {  return current_rwy->b_runway_end_elev_src;}
char * airport::get_b_runway_end_elev_src_date() {  return current_rwy->b_runway_end_elev_src_date;}
char * airport::get_b_dt_pos_src()               {  return current_rwy->b_dt_pos_src;}
char * airport::get_b_dt_pos_src_date()          {  return current_rwy->b_dt_pos_src_date;}
char * airport::get_b_dt_elev_src()              {  return current_rwy->b_dt_elev_src;}
char * airport::get_b_dt_elev_src_date()         {  return current_rwy->b_dt_elev_src_date;}
char * airport::get_b_td_elev_src()              {  return current_rwy->b_td_elev_src;}
char * airport::get_b_td_elev_src_date()         {  return current_rwy->b_td_elev_src_date;}
char * airport::get_b_tora()                     {  return current_rwy->b_tora;}
char * airport::get_b_toda()                     {  return current_rwy->b_toda;}
char * airport::get_b_asda()                     {  return current_rwy->b_asda;}
char * airport::get_b_lda()                      {  return current_rwy->b_lda;}
char * airport::get_b_lahso()                    {  return current_rwy->b_lahso;}
char * airport::get_b_id_int_rw()                {  return current_rwy->b_id_int_rw;}
char * airport::get_b_id_desc_ent()              {  return current_rwy->b_id_desc_ent;}
char * airport::get_b_lat_lahso()                {  return current_rwy->b_lat_lahso;}
char * airport::get_b_lat_lahso_seconds()        {  return current_rwy->b_lat_lahso_seconds;}
char * airport::get_b_lon_lahso()                {  return current_rwy->b_lon_lahso;}
char * airport::get_b_lon_lahso_seconds()        {  return current_rwy->b_lon_lahso_seconds;}
char * airport::get_b_latlon_lahso_src()         {  return current_rwy->b_latlon_lahso_src;}
char * airport::get_b_latlon_lahso_src_date()    {  return current_rwy->b_latlon_lahso_src_date;}
/// ADDITIONAL RECIPROCAL END DATA
char * airport::get_r_runway_end_gradient()      {  return current_rwy->r_runway_end_gradient;}
char * airport::get_r_runway_end_gradient_dir()  {  return current_rwy->r_runway_end_gradient_dir;}
char * airport::get_r_runway_end_pos_src()       {  return current_rwy->r_runway_end_pos_src;}
char * airport::get_r_runway_end_pos_date()      {  return current_rwy->r_runway_end_pos_date;}
char * airport::get_r_runway_end_elev_src()      {  return current_rwy->r_runway_end_elev_src;}
char * airport::get_r_runway_end_elev_src_date() {  return current_rwy->r_runway_end_elev_src_date;}
char * airport::get_r_dt_pos_src()               {  return current_rwy->r_dt_pos_src;}
char * airport::get_r_dt_pos_src_date()          {  return current_rwy->r_dt_pos_src_date;}
char * airport::get_r_dt_elev_src()              {  return current_rwy->r_dt_elev_src;}
char * airport::get_r_dt_elev_src_date()         {  return current_rwy->r_dt_elev_src_date;}
char * airport::get_r_td_elev_src()              {  return current_rwy->r_td_elev_src;}
char * airport::get_r_td_elev_src_date()         {  return current_rwy->r_td_elev_src_date;}
char * airport::get_r_tora()                     {  return current_rwy->r_tora;}
char * airport::get_r_toda()                     {  return current_rwy->r_toda;}
char * airport::get_r_asda()                     {  return current_rwy->r_asda;}
char * airport::get_r_lda()                      {  return current_rwy->r_lda;}
char * airport::get_r_lahso()                    {  return current_rwy->r_lahso;}
char * airport::get_r_id_int_rw()                {  return current_rwy->r_id_int_rw;}
char * airport::get_r_id_desc_ent()              {  return current_rwy->r_id_desc_ent;}
char * airport::get_r_lat_lahso()                {  return current_rwy->r_lat_lahso;}
char * airport::get_r_lat_lahso_seconds()        {  return current_rwy->r_lat_lahso_seconds;}
char * airport::get_r_lon_lahso()                {  return current_rwy->r_lon_lahso;}
char * airport::get_r_lon_lahso_seconds()        {  return current_rwy->r_lon_lahso_seconds;}
char * airport::get_r_latlon_lahso_src()         {  return current_rwy->r_latlon_lahso_src;}
char * airport::get_r_latlon_lahso_src_date()    {  return current_rwy->r_latlon_lahso_src_date;}

bool airport::have_twr1_record()                 {  if (current_apt->twr1 == NULL) return false; current_twr1 = current_apt->twr1; return true;}
char * airport::get_term_com_fac_id()            {  return current_twr1->term_com_fac_id;}
char * airport::get_info_effect_date()           {  return current_twr1->info_effect_date;}
     /// Landing Facility(Airport) Data
char * airport::get_lfsn()                       {  return current_twr1->lfsn;}
char * airport::get_faa_reg_code()               {  return current_twr1->faa_reg_code;}
char * airport::get_assoc_st_name()              {  return current_twr1->assoc_st_name;}
char * airport::get_assoc_st()                   {  return current_twr1->assoc_st;}
char * airport::get_assoc_city_name()            {  return current_twr1->assoc_city_name;}
char * airport::get_offic_apt_name()             {  return current_twr1->offic_apt_name;}
char * airport::get_latitude()                   {  return current_twr1->latitude;}
char * airport::get_latitude_seconds()           {  return current_twr1->latitude_seconds;}
char * airport::get_longitude()                  {  return current_twr1->longitude;}
char * airport::get_longitude_seconds()          {  return current_twr1->longitude_seconds;}
char * airport::get_tie_in_fss()                 {  return current_twr1->tie_in_fss;}
char * airport::get_tie_in_fss_name()            {  return current_twr1->tie_in_fss_name;}
     /// Terminal Communications Facility Data
char * airport::get_fac_type()                   {  return current_twr1->fac_type;}
char * airport::get_num_hours()                  {  return current_twr1->num_hours;}
char * airport::get_num_hours_code()             {  return current_twr1->num_hours_code;}
char * airport::get_master_apt_id()              {  return current_twr1->master_apt_id;}
char * airport::get_master_apt_name()            {  return current_twr1->master_apt_name;}
char * airport::get_dir_find_eq()                {  return current_twr1->dir_find_eq;}
     /// Terminal Communications Facility Off Airport
char * airport::get_assoc_land_fac()             {  return current_twr1->assoc_land_fac;}
char * airport::get_accoc_city()                 {  return current_twr1->accoc_city;}
char * airport::get_st_prov()                    {  return current_twr1->st_prov;}
char * airport::get_st_county()                  {  return current_twr1->st_county;}
char * airport::get_country_st()                 {  return current_twr1->country_st;}
char * airport::get_faa_reg_code_off_apt()       {  return current_twr1->faa_reg_code_off_apt;}
     /// latitude/longitude data
        /// airport surveillance radar
char * airport::get_as_rad_lat()                 {  return current_twr1->as_rad_lat;}
char * airport::get_as_rad_lat_seconds()         {  return current_twr1->as_rad_lat_seconds;}
char * airport::get_as_rad_lon()                 {  return current_twr1->as_rad_lon;}
char * airport::get_as_rad_lon_seconds()         {  return current_twr1->as_rad_lon_seconds;}
     /// direction finding antenna
char * airport::get_dfa_rad_lat()                {  return current_twr1->dfa_rad_lat;}
char * airport::get_dfa_rad_lat_seconds()        {  return current_twr1->dfa_rad_lat_seconds;}
char * airport::get_dfa_rad_lon()                {  return current_twr1->dfa_rad_lon;}
char * airport::get_dfa_rad_lon_seconds()        {  return current_twr1->dfa_rad_lon_seconds;}
     /// Operator Data
char * airport::get_twr()                        {  return current_twr1->twr;}
char * airport::get_mil_ops_data()               {  return current_twr1->mil_ops_data;}
char * airport::get_p_app_cntrl()                {  return current_twr1->p_app_cntrl;}
char * airport::get_s_app_cntrl()                {  return current_twr1->s_app_cntrl;}
char * airport::get_p_dep_cntrl()                {  return current_twr1->p_dep_cntrl;}
char * airport::get_s_dep_cntrl()                {  return current_twr1->s_dep_cntrl;}
     /// radio call data
char * airport::get_pilot_to_twr()               {  return current_twr1->pilot_to_twr;}
char * airport::get_mill_ops_call()              {  return current_twr1->mill_ops_call;}
char * airport::get_p_app_cntr_call()            {  return current_twr1->p_app_cntr_call;}
char * airport::get_p_take_over_cntrl_call()     {  return current_twr1->p_take_over_cntrl_call;}
char * airport::get_p_dep_cntr()                 {  return current_twr1->p_dep_cntr;}
char * airport::get_d_take_over_dep_cntrl()      {  return current_twr1->d_take_over_dep_cntrl;}

bool airport::have_twr2_record()                 { if (current_twr1->twr2 == NULL) return false; twr2 = current_twr1->twr2; return true;}
char * airport::get_ident()                      {  return twr2->ident;}
char * airport::get_pmsv()                       {  return twr2->pmsv;}
char * airport::get_macp()                       {  return twr2->macp;}
char * airport::get_dyly()                       {  return twr2->dyly;}
char * airport::get_p_app()                      {  return twr2->p_app;}
char * airport::get_s_app()                      {  return twr2->s_app;}
char * airport::get_p_dep()                      {  return twr2->p_dep;}
char * airport::get_s_dep()                      {  return twr2->s_dep;}
char * airport::get_twr2_twr()                   {  return twr2->twr;}

bool airport::have_twr3_records()                {  current_twr3 = current_twr1->twr3_list;  if (current_twr3 != NULL) return true; else return false;}
bool airport::next_twr3_record()                 {  if (current_twr3->next_twr3 != NULL) { current_twr3 = current_twr3->next_twr3; return true;  }  else return false;}
char * airport::get_twr3_ident()                 {  return current_twr3->ident;}
char * airport::get_twr3_freq(int i)             {  return (char *)current_twr3->freq[i];}
char * airport::get_twr3_use(int i)              {  return (char *)current_twr3->use[i];}
char * airport::get_freq_not_trunc(int i)        {  return (char *)current_twr3->freq_not_trunc[i];}

bool airport::have_twr4_records()                {  current_twr4 = current_twr1->twr4_list; if (current_twr4 != NULL) return true; else return false;}
bool airport::next_twr4_record()                 {  if (current_twr4->next_twr4 != NULL) { current_twr4 = current_twr4->next_twr4; return true;}  else return false;}
char * airport::get_twr4_ident()                 {  return current_twr4->ident;}
char * airport::get_service()                    {  return current_twr4->service;}

bool airport::have_twr5_record()                 {  twr5 = current_twr1->twr5; if (twr5 != NULL) return true; else return false;}
char * airport::get_twr5_ident()                 {  return twr5->ident;}
char * airport::get_p_apr_call()                 {  return twr5->p_apr_call;}
char * airport::get_s_apr_call()                 {  return twr5->s_app_call;}
char * airport::get_p_dep_call()                 {  return twr5->p_dpt_call;}
char * airport::get_s_dep_call()                 {  return twr5->s_dpt_call;}
char * airport::get_radar_type(int i)            {  return (char *)twr5->radar_type[i];}
char * airport::get_radar_hrs(int i)             {  return (char *)twr5->radar_hrs[i];}

bool airport::have_twr6_records()                {  current_twr6 = current_twr1->twr6_list;  if (current_twr6 != NULL) return true; else return false;}
bool airport::next_twr6_record()                 {  if (current_twr6->next_twr6 != NULL) { current_twr6 = current_twr6->next_twr6; return true; } else return false;}
char * airport::get_twr6_ident()                 {  return current_twr6->ident;}
char * airport::get_twr6_elem_nbr()              {  return current_twr6->elem_nbr;}
char * airport::get_twr6_remark()                {  return current_twr6->remark;}

bool airport::have_twr7_records()                {  current_twr7 = current_twr1->twr7_list;  if (current_twr7 != NULL) return true; else return false;}
bool airport::next_twr7_record()                 {  if (current_twr7->next_twr7 != NULL) { current_twr7 = current_twr7->next_twr7; return true; }  else return false;}
char * airport::get_twr7_ident()                 {  return current_twr7->ident;}
char * airport::get_twr7_sat_freq()              {  return current_twr7->sat_freq;}
char * airport::get_twr7_sat_use()               {  return current_twr7->sat_use;}
char * airport::get_twr7_apt_site_nbr()          {  return current_twr7->apt_site_nbr;}
char * airport::get_twr7_apt_id()                {  return current_twr7->apt_id;}
char * airport::get_twr7_faa_reg()               {  return current_twr7->faa_reg;}
char * airport::get_twr7_st_name()               {  return current_twr7->st_name;}
char * airport::get_twr7_st()                    {  return current_twr7->st;}
char * airport::get_twr7_city()                  {  return current_twr7->city;}
char * airport::get_twr7_arpt_name()             {  return current_twr7->arpt_name; }
char * airport::get_twr7_lat()                   {  return current_twr7->lat;}
char * airport::get_twr7_lat_seconds()           {  return current_twr7->lat_seconds;}
char * airport::get_twr7_lon()                   {  return current_twr7->lon;}
char * airport::get_twr7_lon_seconds()           {  return current_twr7->lon_seconds;}
char * airport::get_twr7_fss_id()                {  return current_twr7->fss_id;}
char * airport::get_twr7_fss_name()              {  return current_twr7->fss_name;}
      /// Master Airport Information //
char * airport::get_twr7_m_arpt_id()             {  return current_twr7->m_arpt_id;}
char * airport::get_twr7_m_faa_reg()             {  return current_twr7->m_faa_reg;}
char * airport::get_twr7_m_st_name()             {  return current_twr7->m_st_name;}
char * airport::get_twr7_m_st()                  {  return current_twr7->m_st;}
char * airport::get_twr7_m_city()                {  return current_twr7->m_city;}
char * airport::get_twr7_m_arpt_name()           {  return current_twr7->m_arpt_name;}
char * airport::get_twr7_m_sat_freq()            {  return current_twr7->sat_freq;}

bool airport::have_twr8_record()                 {  twr8 = current_twr1->twr8; if (twr8 != NULL) return true; else return false;}
char * airport::get_twr8_ident()                 {  return twr8->ident;}
char * airport::get_twr8_class_b()               {  return twr8->class_b;}
char * airport::get_twr8_class_c()               {  return twr8->class_c;}
char * airport::get_twr8_class_d()               {  return twr8->class_d;}
char * airport::get_twr8_class_e()               {  return twr8->class_e;}
char * airport::get_twr8_hours()                 {  return twr8->hours;}

bool airport::have_twr9_records()                {  current_twr9 = current_twr1->twr9_list; if (current_twr9 != NULL) return true; else return false;}
bool airport::next_twr9_record()                 {  if (current_twr9->next_twr9 != NULL) { current_twr9 = current_twr9->next_twr9; return true; }  else return false;}
char * airport::get_twr9_ident()                 {  return current_twr9->ident;}
char * airport::get_twr9_sn()                    {  return current_twr9->sn;}
char * airport::get_twr9_hours()                 {  return current_twr9->hours;}
char * airport::get_twr9_purpose()               {  return current_twr9->purpose;}
char * airport::get_twr9_phone()                 {  return current_twr9->phone;}

bool airport::have_awos1_record()               {  if (current_apt->awos1 == NULL) return false; current_awos1 = current_apt->awos1; return true; }

char * airport::get_awos1_wx_sensor_ident()               {  return current_awos1->wx_sensor_ident;   }
char * airport::get_awos1_wx_sensor_type()                {  return current_awos1->wx_sensor_type;   }
char * airport::get_awos1_commisioning_status()           {  return current_awos1->commisioning_status;   }
char * airport::get_awos1_commisioning_date()             {  return current_awos1->commisioning_date;   }
char * airport::get_awos1_navaid_flag()                   {  return current_awos1->navaid_flag;   }
char * airport::get_awos1_lat()                           {  return current_awos1->lat;   }
char * airport::get_awos1_lon()                           {  return current_awos1->lon;   }
char * airport::get_awos1_elevation()                     {  return current_awos1->elevation;   }
char * airport::get_awos1_survey_method()                 {  return current_awos1->survey_method;   }
char * airport::get_awos1_frequency()                     {  return current_awos1->frequency;   }
char * airport::get_awos1_frequency2()                    {  return current_awos1->frequency2;   }
char * airport::get_awos1_phone()                         {  return current_awos1->phone;   }
char * airport::get_awos1_phone2()                        {  return current_awos1->phone2;   }
char * airport::get_awos1_lfsn()                          {  return current_awos1->lfsn;   }
char * airport::get_awos1_city()                          {  return current_awos1->city;   }
char * airport::get_awos1_st()                            {  return current_awos1->st;   }
char * airport::get_awos1_info_eff_date()                 {  return current_awos1->info_eff_date;   }

bool airport::have_awos2_records()               {  current_awos2 = current_awos1->awos2_list; if(current_awos2 != NULL) return true; else return false; }
bool airport::next_awos2_record()                {  if (current_awos2->next_awos2 != NULL) {current_awos2 =current_awos2->next_awos2; return true; } else return false; }
char * airport::get_awos2_wx_sensor_ident()      {  return current_awos2->wx_sensor_ident; }
char * airport::get_awos2_wx_sensor_type()       {  return current_awos2->wx_sensor_type; }
char * airport::get_awos2_remarks()              {  return current_awos2->remarks; }

void airport::process_nav6_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_nav6->nav_fac_id,4,4);         //L AN 0004 00005  DLID    NAVAID FACILITY IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_nav6->fac_type,20,8);          //L AN 0020 00009  DLID    NAVAID FACITITY TYPE (EX: VOR/DME)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav6->air_grnd,2,28);          //L AN 0002 00029  N/A     AIR/GROUND CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_nav6->brng_of_chk_pnt,3,30);   //R  N 0003 00031  N/A     BEARING OF CHECKPOINT
  set_field((char *)&NASRairportbuffer,(char *)&current_nav6->alt_only,5,33);          //R  N 0005 00034  N/A     ALTITUDE ONLY WHEN CHECKPOINT IS IN AIR
  set_field((char *)&NASRairportbuffer,(char *)&current_nav6->apt_id,4,38);            //L AN 0004 00039  N/A     AIRPORT ID
  set_field((char *)&NASRairportbuffer,(char *)&current_nav6->st,2,42);                //L AN 0002 00043  N/A     STATE CODE IN WHICH ASSOCIATED CITY IS LOCATED
  set_field((char *)&NASRairportbuffer,(char *)&current_nav6->narrative,75,44);        //L AN 0075 00045  N/A     NARRATIVE DESCRIPTION ASSOCIATED WITH
  set_field((char *)&NASRairportbuffer,(char *)&current_nav6->description,75,119);     //L AN 0075 00120  N/A     NARRATIVE DESCRIPTION ASSOCIATED WITH
}
void airport::process_nav5_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_nav5->nav_fac_id,4,4);           //L AN 0004 00005  DLID    NAVAID FACILITY IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_nav5->fac_type,20,9);            //L AN 0020 00009  DLID    NAVAID FACITITY TYPE (EX: VOR/DME)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav5->fm_names,30,28);            //L AN 0030 00029  N81     NAME(S) OF FAN MARKER(S)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav5->fm_extra_names,690,58);     //L AN 0690 00059  N/A     SPACE ALLOCATED FOR 23 MORE FAN MARKERS
}
void airport::process_nav4_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_nav4->nav_fac_id,4,4);           //L AN 0004 00005  DLID    NAVAID FACILITY IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_nav4->fac_type,20,8);            //L AN 0020 00009  DLID    NAVAID FACITITY TYPE (EX: VOR/DME)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav4->hp_names,80,28);            //L AN 0080 00029  N84     NAME(S) OF HOLDING PATTERN(S)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav4->hp_nbr,3,108);               //R  N 0003 00109          PATTERN (NUMBER) OF THE HOLDING PATTERN
  set_field((char *)&NASRairportbuffer,(char *)&current_nav4->extra_hp,664,111);           //L AN 0664 00112          SPACE ALLOCATED FOR 8 MORE HOLDING PATTERNS.
}
void airport::process_nav3_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_nav3->nav_fac_id,4,4);           //L AN 0004 00005  DLID    NAVAID FACILITY IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_nav3->fac_type,20,8);            //L AN 0020 00009  DLID    NAVAID FACITITY TYPE (EX: VOR/DME)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav3->fixes,36,28);               //L AN 0036 00029  N83     NAME(S) OF FIXES (FIX-FILE), THE ID'(S) OF
  set_field((char *)&NASRairportbuffer,(char *)&current_nav3->extra_fixes,720,64);        //L AN 0720 00065  N/A     SPACE ALLOCATED FOR 20 MORE FIXES
}
void airport::process_nav2_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_nav2->nav_fac_id,4,4);            //L AN 0004 00005  DLID    NAVAID FACILITY IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_nav2->fac_type,20,8);             //L AN 0020 00009  DLID    NAVAID FACITITY TYPE (EX: VOR/DME)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav2->remarks,600,28);            //L AN 0600 00029  RMRKS   NAVAID REMARKS. FREE FORM TEXT
}
void airport::process_nav1_record()
{
 /// BASIC NAVAID INFORMATION
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->nav_fac_id,4,4);             //L AN 0004 00005  DLID    NAVAID FACILITY IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->fac_type,20,8);              //L AN 0020 00009  DLID    NAVAID FACILITY TYPE (SEE DESCRIPTION)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->official_fac_id,4,28);       //L AN 0004 00029 DLID     OFFICIAL NAVAID FACILITY IDENTIFIER
  /// ADMINISTRATIVE   DATA
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->eff_date,10,32);             //L AN 0010 00033  N/A     EFFECTIVE DATE; THIS DATE COINCIDES WITH
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->name,30,42);                 //L AN 0030 00043  N8      NAME OF NAVAID.(EX: WASHINGTON)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->city,40,72);                 //L AN 0040 00073  N1      CITY ASSOCIATED WITH THE NAVAID.
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->state_name,30,112);          //L AN 0030 00113  N2      STATE NAME WHERE ASSOCIATED CITY IS LOCATED
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->st,2,142);                   //L AN 0002 00143  N2S     STATE POST OFFICE CODE WHERE ASSOCIATED
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->faa_reg,3,144);              //L AN 0003 00145  N20     FAA REGION RESPONSIBLE FOR NAVAID (CODE)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->country_other,30,147);       //L AN 0030 00148  N3      COUNTRY NAVAID LOCATED IF OTHER THAN U.S
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->other_postal,2,177);         //L AN 0002 00178  N3S     COUNTRY POST OFFICE CODE NAVAID
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->owner,50,179);               //L AN 0050 00180  N10     NAVAID OWNER NAME  (EX: U.S. NAVY)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->oper_name,50,229);           //L AN 0050 00230  N12     NAVAID OPERATOR NAME (EX: U.S. NAVY)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->com_sys_use,1,279);          //L AN 0001 00280  N47     COMMON SYSTEM USAGE (Y OR N)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->public_use,1,280);           //L AN 0001 00281  N48     NAVAID PUBLIC USE (Y OR N)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->nav_class,11,281);           //L AN 0011 00282  N28     CLASS OF NAVAID.
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->hours,11,292);               //L AN 0011 00293  N52     HOURS OF OPERATION OF NAVAID
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->artcc_h_bndry,4,303);        //L AN 0004 00304  N91     IDENTIFIER OF ARTCC WITH HIGH ALTITUDE BOUNDARY THAT THE NAVAID
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->name_h_artcc,30,307);        //L AN 0030 00308  N91     NAME OF ARTCC WITH HIGH ALTITUDE BOUNDARY THAT THE NAVAID
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->artcc_l_bndry,4,337);        //L AN 0004 00338  N94     IDENTIFIER OF ARTCC WITH LOW ALTITUDE BOUNDARY THAT THE NAVAID
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->name_l_artcc,30,341);        //L AN 0030 00342  N94     NAME OF ARTCC WITH LOW ALTITUDE BOUNDARY THAT THE NAVAID
  /// GEOGRAPHIC POSITION DATA                                                         //
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->lat,14,371);                 //L AN 0014 00372  N4      NAVAID LATITUDE (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->lat_seconds,11,385);         //L AN 0011 00386  N4S     NAVAID LATITUDE (ALL SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->lon,14,396);                 //L AN 0014 00397  N5      NAVAID LONGITUDE (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->lon_seconds,11,410);         //L AN 0011 00411  N5S     NAVAID LONGITUDE (ALL SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->accuracy,1,421);             //L AN 0001 00422  N38     LATITUDE/LONGITUDE SURVERY ACCURACY (CODE)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->lat_tacan,14,422);           //L AN 0014 00423  N21     LATITUDE OF TACAN PORTION OF VORTAC WHEN TACAN
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->lat_tacan_seconds,11,436);   //L AN 0011 00437  N21S    LATITUDE OF TACAN PORTION OF VORTAC WHEN TACAN
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->lon_tacan,14,447);           //L AN 0014 00448  N22     LONGITUDE OF TACAN PORTION OF VORTAC WHEN TACAN
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->lon_tacan_seconds,11,461);   //L AN 0011 00462  N22S    LONGITUDE OF TACAN PORTION OF VORTAC WHEN TACAN
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->elevation,6,472);            //R AN 0007 00473  N37     ELEVATION IN TENTH OF A FOOT (MSL)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->mag_var,5,479);              //R AN 0005 00480  N45      MAGNETIC VARIATION DEGREES   (00-99)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->mag_epoch_yr,4,484);         //R AN 0004 00485  N45S     MAGNETIC VARIATION EPOCH YEAR  (00-99)
      /// FACILITIES/FEATURES OF NAVAID                                                //
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->voice,3,488);                //L AN 0003 00489 N33     SIMULTANEOUS VOICE FEATURE (Y,N, OR NULL)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->watts,4,491);                //R  N 0004 00492 N34     POWER OUTPUT (IN WATTS)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->auto_voice_id,3,495);        //L AN 0003 00496 N35     AUTOMATIC VOICE IDENTIFICATION FEATURE
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->mon_cat,1,498);              //L AN 0001 00499 N36     MONITORING CATEGORY
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->radio_call,30,499);          //L AN 0030 00500 N23     RADIO VOICE CALL (NAME)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->channel,4,529);              //L AN 0004 00530 N24     CHANNEL (TACAN)  NAVAID TRANSMITS ON
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->freq,6,533);                 //R  N 0006 00534 N25     FREQUENCY THE NAVAID TRANSMITS ON
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->fan_id,24,539);              //R  N 0024 00540 N75     TRANSMITTED FAN MARKER/MARINE RADIO BEACON
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->fan_type,10,563);            //L AN 0010 00564 N76     FAN MARKER TYPE (BONE OR ELLIPTICAL)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->tr_bearng_fm,3,573);         //L AN 0003 00574 N77     TRUE BEARING OF MAJOR AXIS OF FAN MARKER
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->prot_alt_freq,1,578);        //L AN 0002 00579 N29     PROTECTED FREQUENCY ALTITUDE
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->lo_alt_use,3,580);           //L AN 0003 00581 N30     LOW ALTITUDE FACILITY USED IN HIGH STRUCTURE
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->z_marker,3,583);             //L AN 0003 00584 N31     NAVAID Z MARKER AVAILABLE (Y, N, OR NULL)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->twx_bx_hrs,9,586);           //L AN 0009 00587 N32     TRANSCRIBED WEATHER BROADCAST HOURS (TWEB)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->twx_wx_ph,20,595);           //L AN 0020 00596 N95     TRANSCRIBED WEATHER BROADCAST PHONE NUMBER
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->fss_ident,4,615);            //L AN 0004 00616 N49S    ASSOCIATED/CONTROLLING FSS (IDENT)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->fss_name,30,619);            //L AN 0030 00620 N49     ASSOCIATED/CONTROLLING FSS (NAME)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->op_hrs,100,649);             //L AN 0100 00650 F15     HOURS OF OPERATION OF CONTROLLING FSS
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->notam_ident,4,749);          //L AN 0004 00750 N49B    NOTAM ACCOUNTABILITY CODE (IDENT)
      /// CHARTING DATA                                                                //
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->quad_id_rng_brg,16,753);     //L AN 0016 00754 N80     QUADRANT IDENTIFICATION AND RANGE LEG BEARING
      /// NAVAID STATUS                                                                //
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->nav_status,30,769);          //L AN 0030 00770  N41,    NAVIGATION AID STATUS
      /// PITCH, CATCH AND SUA/ATCAA FLAGS                                             //
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->pitch_flg,1,799);            //L AN 0001 00800  N/A    PITCH FLAG (Y OR N)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->catch_flg,1,800);            //L AN 0001 00801  N/A    CATCH FLAG (Y OR N)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->sua_flg,1,801);              //L AN 0001 00802  N/A    SUA/ATCAA FLAG (Y OR N)
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->rest_flg,1,802);             //L AN 0001 00803  N/A    NAVAID RESTRICTION FLAG
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->hiwas_flg,1,803);            //L AN 0001 00804  N/A    HIWAS FLAG
  set_field((char *)&NASRairportbuffer,(char *)&current_nav1->tweb_restrict,1,804);        //L AN 0001 00805  N/A    TRANSCRIBED WEATHER BROADCAST (TWEB) RESTRICTION
}

void airport::process_fix5_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_fix5->fix_id,30,4);      //L  AN0030 00005  NONE    RECORD IDENTIFIER (FIX NAME)
  set_field((char *)&NASRairportbuffer,(char *)&current_fix5->fix_st_name,30,34); //L  AN0030 00035  NONE    RECORD IDENTIFIER (FIX STATE NAME)
  set_field((char *)&NASRairportbuffer,(char *)&current_fix5->ICAO_reg,2,64);     //L  AN0002 00065  NONE    ICAO REGION CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_fix5->chart,22,66);       //L  AN0022 00067  FX21    CHART ON WHICH FIX IS TO BE DEPICTED
}
void airport::process_fix4_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_fix4->fix_id,30,4);     //L  AN0030 00005  NONE    RECORD IDENTIFIER (FIX NAME)
  set_field((char *)&NASRairportbuffer,(char *)&current_fix4->fix_st_name,30,34);//L  AN0030 00035  NONE    RECORD IDENTIFIER (FIX STATE NAME)
  set_field((char *)&NASRairportbuffer,(char *)&current_fix4->ICAO_reg,2,64);    //L  AN0002 00065  NONE    ICAO REGION CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_fix4->label,100,66);     //L  AN0100 00067  NONE    FIELD LABEL
  set_field((char *)&NASRairportbuffer,(char *)&current_fix4->remark,300,166);    //L  AN0300 00167  NONE    REMARK TEXT
}
void airport::process_fix3_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_fix3->fix_id,30,4);     //L  AN0030 00005  NONE    RECORD IDENTIFIER (FIX NAME)
  set_field((char *)&NASRairportbuffer,(char *)&current_fix3->fix_st_name,30,34);//L  AN0030 00035  NONE    RECORD IDENTIFIER (FIX STATE NAME)
  set_field((char *)&NASRairportbuffer,(char *)&current_fix3->ICAO_reg,2,64);    //L  AN0002 00065  NONE    ICAO REGION CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_fix3->loc_id,23,66);     //L  AN0023 00067  FX26    3 OR 4 LETTER IDENT*FACILITY TYPE*DIRECTION OR COURSE
}

void airport::process_fix2_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_fix2->fix_id,30,4);     //L  AN0030 00005  NONE    RECORD IDENTIFIER (FIX NAME)
  set_field((char *)&NASRairportbuffer,(char *)&current_fix2->fix_st_name,30,34);//L  AN0030 00035  NONE    RECORD IDENTIFIER (FIX STATE NAME)
  set_field((char *)&NASRairportbuffer,(char *)&current_fix2->ICAO_reg,2,64);    //L  AN0002 00065  NONE    ICAO REGION CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_fix2->loc_id,23,66);     //L  AN0023 00067  FX22    LOCATION-IDENTIFIER, FACILITY TYPE, AND RADIAL
}

void airport::process_fix1_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->fix_id,30,4);      //L  AN0030 00005  NONE    RECORD IDENTIFIER (FIX ID)
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->fix_st_name,30,34); //L  AN0030 00035  NONE    RECORD IDENTIFIER (FIX STATE NAME)
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->ICAO_reg,2,64);     //L  AN0002 00065  NONE    ICAO REGION CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->lat,14,66);         //L  AN0014 00067  FX4     GEOGRAPHICAL LATITUDE OF THE FIX.
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->lon,14,80);         //L  AN0014 00081  FX5     GEOGRAPHICAL LONGITUDE OF THE FIX.
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->civil_cat,3,94);    //L  AN0003 00095  FX20    CATEGORIZES THE FIX AS A MILITARY (MIL),
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->ident_fac,22,97);   //L  AN0022 00098  FX27    3 OR 4 LETTER IDENT*FACILITY TYPE*DIRECTION OR
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->apt_rwy_id,22,119);  //L  AN0022 00120  FX27    AIRPORT ID*APPROACH-END-RWY*DISTANCE OF RADAR COMPONENT
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->prev_name,33,141);   //L  AN0033 00142  FX33    PREVIOUS NAME OF THE FIX BEFORE IT WAS RENAMED
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->charting,38,174);    //L  AN0038 00175  FX31    CHARTING INFORMATION.
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->published,1,212);    //L  AN0001 00213  FX34    FIX TO BE PUBLISHED (Y = YES OR N = NO)
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->use,15,213);         //L  AN0015 00214  FX36    FIX USE
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->NAS_id,5,228);       //L  AN0005 00229  FX37    NATIONAL AIRSPACE SYSTEM(NAS) IDENTIFIER FOR
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->high_juris,4,233);   //L  AN0004 00234  FX91    DENOTES HIGH ARTCC AREA OF JURISDICTION.
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->low_juris,4,237);    //L  AN0004 00238  NONE    DENOTES LOW ARTCC AREA OF JURISDICTION.
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->country_name,30,241);//L  AN0030 00242  NONE    FIX COUNTRY NAME (OUTSIDE CONUS)
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->pitch_flg,1,271);    //L  AN0001 00272  NONE    PITCH (Y = YES OR N = NO)
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->catch_flg,1,272);    //L  AN0001 00273  NONE    CATCH (Y = YES OR N = NO)
  set_field((char *)&NASRairportbuffer,(char *)&current_fix1->sua_flg,1,274);      //L  AN0001 00274  NONE    SUA/ATCAA (Y = YES OR N = NO)
}


void airport::process_awos1_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_awos1->wx_sensor_ident,4,5);      //L  AN  0004 00006  N/A     WX SENSOR IDENT
  set_field((char *)&NASRairportbuffer,(char *)&current_awos1->wx_sensor_type,10,9);      //L  AN  0010 00010  N/A     WX SENSOR TYPE
  set_field((char *)&NASRairportbuffer,(char *)&current_awos1->commisioning_status,1,19); //L  AN  0001 00020  N/A     COMMISSIONING STATUS
  set_field((char *)&NASRairportbuffer,(char *)&current_awos1->commisioning_date,10,20);  //L  AN  0010 00021  N/A     COMMISSIONING/DECOMMISSIONING DATE (MM/DD/YYYY)
  set_field((char *)&NASRairportbuffer,(char *)&current_awos1->navaid_flag,1,30);         //L  AN  0001 00031  N/A     NAVAID FLAG - WX SENSOR ASSOCIATED WITH NAVAID
  set_field((char *)&NASRairportbuffer,(char *)&current_awos1->lat,14,31);                //L  AN  0014 00032  N/A     STATION LATITUDE
  set_field((char *)&NASRairportbuffer,(char *)&current_awos1->lon,15,45);                //L  AN  0015 00046  N/A     STATION LONGITUDE
  set_field((char *)&NASRairportbuffer,(char *)&current_awos1->elevation,7,60);           //L  AN  0007 00061  N/A     ELEVATION
  set_field((char *)&NASRairportbuffer,(char *)&current_awos1->survey_method,1,67);       //L  AN  0001 00068  N/A     SURVEY METHOD CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_awos1->frequency,7,68);           //L  AN  0007 00069  N/A     STATION FREQUENCY
  set_field((char *)&NASRairportbuffer,(char *)&current_awos1->frequency2,7,75);          //L  AN  0007 00076  N/A     SECOND STATION FREQUENCY
  set_field((char *)&NASRairportbuffer,(char *)&current_awos1->phone,14,82);              //L  AN  0014 00083  N/A     STATION TELEPHONE NUMBER
  set_field((char *)&NASRairportbuffer,(char *)&current_awos1->phone2,14,96);             //L  AN  0014 00097  N/A     SECOND STATION TELEPHONE NUMBER
  set_field((char *)&NASRairportbuffer,(char *)&current_awos1->lfsn,11,110);              //L  AN  0011 00111  A0      LANDING FACILITY SITE NUMBER WHEN STATION LOCATED
  set_field((char *)&NASRairportbuffer,(char *)&current_awos1->city,40,121);              //L  AN  0040 00122  N/A     STATION CITY
  set_field((char *)&NASRairportbuffer,(char *)&current_awos1->st,2,161);                 //L  AN  0002 00162  N/A     STATION STATE POST OFFICE CODE (EX. IL)
  set_field((char *)&NASRairportbuffer,(char *)&current_awos1->info_eff_date,10,163);     //L  AN  0010 00164  N/A     INFORMATION EFFECTIVE DATE (MM/DD/YYYY)
}
void airport::process_awos2_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_awos2->wx_sensor_ident,4,5);      //L AN  0004 00006  N/A      WX SENSOR IDENT
  set_field((char *)&NASRairportbuffer,(char *)&current_awos2->wx_sensor_type,10,9);      //L AN  0010 00010  N/A      WX SENSOR TYPE
  set_field((char *)&NASRairportbuffer,(char *)&current_awos2->remarks,236,19);           //L AN  0236 00020  RMRKS    ASOS/AWOS REMARKS, FREE-FORM TEXT.
}

/// ILS RECORDS
bool airport::have_apt_ils_records()
{
  if (current_apt->ils_list != NULL) {
    current_apt_ils = current_apt->ils_list;
    current_ils1 = current_apt_ils->apt_ils1;
    return true;
  } else return false;
}
bool airport::next_apt_ils_record() {
  if (current_apt_ils->next_apt_ils != NULL) {
    current_apt_ils = current_apt_ils->next_apt_ils;
    current_ils1 = current_apt_ils->apt_ils1;
    return true;
  }
  else return false;
}
bool airport::have_ils1_records() { current_ils1 = head_ils1;  if (current_ils1 != NULL) return true; else return false; }
bool airport::next_ils1_record()  { if (current_ils1->next_ils1 != NULL) {current_ils1 = current_ils1->next_ils1; return true; } else return false; }
bool airport::have_ils2_record()  { if (current_ils1->ils2 != NULL) { ils2 = current_ils1->ils2; return true; } else return false; }
bool airport::have_ils3_record()  { if (current_ils1->ils3 != NULL) { ils3 = current_ils1->ils3; return true; } else return false; }
bool airport::have_ils4_record()  { if (current_ils1->ils4 != NULL) { ils4 = current_ils1->ils4; return true; } else return false; }
bool airport::have_ils5_records() { if (current_ils1->ils5_list != NULL) { current_ils5 = current_ils1->ils5_list; return true; } else return false; }
bool airport::next_ils5_record()  { if (current_ils5->next_ils5 != NULL) { current_ils5 = current_ils5->next_ils5; return true; } else return false; }
bool airport::have_ils6_records() { if (current_ils1->ils6_list != NULL) { current_ils6 = current_ils1->ils6_list; return true; } else return false; }
bool airport::next_ils6_record()  { if (current_ils6->next_ils6 != NULL) { current_ils6 = current_ils6->next_ils6; return true; } else return false; }

  /// ILS AIRPORT/RUNWAY INFORMATION
char * airport::get_ils1_lfsn()        { return current_ils1->lfsn; }
char * airport::get_ils1_rwy_end()     { return current_ils1->rwy_end; }
char * airport::get_ils1_type()        { return current_ils1->type; }
char * airport::get_ils1_id_code()     { return current_ils1->id_code; }
char * airport::get_ils1_eff_date()    { return current_ils1->eff_date; }
char * airport::get_ils1_apt_name()    { return current_ils1->apt_name; }
char * airport::get_ils1_city()        { return current_ils1->city; }
char * airport::get_ils1_st()          { return current_ils1->st; }
char * airport::get_ils1_state_name()  { return current_ils1->state_name; }
char * airport::get_ils1_faa_reg()     { return current_ils1->faa_reg; }
char * airport::get_ils1_apt_id()      { return current_ils1->apt_id; }
char * airport::get_ils1_length()      { return current_ils1->length; }
char * airport::get_ils1_width()       { return current_ils1->width; }
  /// ILS SYSTEM INFORMATION
char * airport::get_ils1_cat()             { return current_ils1->cat; }
char * airport::get_ils1_own_name()        { return current_ils1->own_name; }
char * airport::get_ils1_fac_oper()        { return current_ils1->fac_oper; }
char * airport::get_ils1_app_bearing_mag() { return current_ils1->app_bearing_mag; }
char * airport::get_ils1_mag_var()         { return current_ils1->mag_var; }

/// ILS2 RECORD /// LOCALIZER DATA
char * airport::get_ils2_lfsn()                { return ils2->lfsn; }
char * airport::get_ils2_rwy_end()             { return ils2->rwy_end; }
char * airport::get_ils2_type()                { return ils2->type; }
char * airport::get_ils2_status()              { return ils2->status; }
char * airport::get_ils2_eff_date()            { return ils2->eff_date; }
char * airport::get_ils2_lat_ant()             { return ils2->lat_ant; }
char * airport::get_ils2_lat_ant_seconds()     { return ils2->lat_ant_seconds; }
char * airport::get_ils2_lon_ant()             { return ils2->lon_ant; }
char * airport::get_ils2_lon_ant_seconds()     { return ils2->lon_ant_seconds; }
char * airport::get_ils2_lat_lon_code()        { return ils2->lat_lon_code; }
char * airport::get_ils2_dist_frm_app_end()    { return ils2->dist_frm_app_end; }
char * airport::get_ils2_dist_frm_rnwy_cl()    { return ils2->dist_frm_rnwy_cl; }
char * airport::get_ils2_dir_of_ant_frm_rnwy() { return ils2->dir_of_ant_frm_rnwy; }
char * airport::get_ils2_src_dist_info()       { return ils2->src_dist_info; }
char * airport::get_ils2_elev()                { return ils2->elev; }
char * airport::get_ils2_freq_mhz()            { return ils2->freq_mhz; }
char * airport::get_ils2_back_crs_status()     { return ils2->back_crs_status; }
char * airport::get_ils2_course_width()        { return ils2->course_width; }
char * airport::get_ils2_width_at_threshold()  { return ils2->width_at_threshold;}
char * airport::get_ils2_dist_from_stop()      { return ils2->dist_from_stop; }
char * airport::get_ils2_dir_from_stop()       { return ils2->dir_from_stop; }
char * airport::get_ils2_serv_code()           { return ils2->serv_code; }

/// ILS3 RECORD///GLIDE SLOPE DATA
char * airport::get_ils3_lfsn()                { return ils3->lfsn; }
char * airport::get_ils3_rwy_end()             { return ils3->rwy_end; }
char * airport::get_ils3_type()                { return ils3->type; }
char * airport::get_ils3_status()              { return ils3->status; }
char * airport::get_ils3_eff_date()            { return ils3->eff_date; }
char * airport::get_ils3_lat_ant()             { return ils3->lat_ant; }
char * airport::get_ils3_lat_ant_seconds()     { return ils3->lat_ant_seconds; }
char * airport::get_ils3_lon_ant()             { return ils3->lon_ant; }
char * airport::get_ils3_lon_ant_seconds()     { return ils3->lon_ant_seconds; }
char * airport::get_ils3_lat_lon_code()        { return ils3->lat_lon_code; }
char * airport::get_ils3_dist_frm_app_end()    { return ils3->dist_frm_app_end; }
char * airport::get_ils3_dist_frm_rnwy_cl()    { return ils3->dist_frm_rnwy_cl; }
char * airport::get_ils3_dir_of_ant_frm_rnwy() { return ils3->dir_of_ant_frm_rnwy; }
char * airport::get_ils3_src_dist_info()       { return ils3->src_dist_info; }
char * airport::get_ils3_elev()                { return ils3->elev; }
char * airport::get_ils3_gsclass()             { return ils3->gsclass; }
char * airport::get_ils3_angle()               { return ils3->angle; }
char * airport::get_ils3_freq()                { return ils3->freq; }
char * airport::get_ils3_adj_elev()            { return ils3->adj_elev; }

/// ILS4  ///DISTANCE MEASURING EQUIPMENT (DME) DATA
char * airport::get_ils4_lfsn()                { return ils4->lfsn; }
char * airport::get_ils4_rwy_end()             { return ils4->rwy_end; }
char * airport::get_ils4_type()                { return ils4->type; }
char * airport::get_ils4_status()              { return ils4->status; }
char * airport::get_ils4_eff_date()            { return ils4->eff_date; }
char * airport::get_ils4_lat_ant()             { return ils4->lat_ant; }
char * airport::get_ils4_lat_ant_seconds()     { return ils4->lat_ant_seconds; }
char * airport::get_ils4_lon_ant()             { return ils4->lon_ant; }
char * airport::get_ils4_lon_ant_seconds()     { return ils4->lon_ant_seconds; }
char * airport::get_ils4_lat_lon_code()        { return ils4->lat_lon_code; }
char * airport::get_ils4_dist_frm_app_end()    { return ils4->dist_frm_app_end; }
char * airport::get_ils4_dist_frm_rnwy_cl()    { return ils4->dist_frm_rnwy_cl; }
char * airport::get_ils4_dir_of_ant_frm_rnwy() { return ils4->dir_of_ant_frm_rnwy; }
char * airport::get_ils4_src_dist_info()       { return ils4->src_dist_info; }
char * airport::get_ils4_elev()                { return ils4->elev; }
char * airport::get_ils4_channel()             { return ils4->channel; }
char * airport::get_ils4_dist_frm_stop()       { return ils4->dist_frm_stop; }

/// ILS5  ///MARKER BEACON DATA
char * airport::get_ils5_lfsn()                 { return current_ils5->lfsn; }
char * airport::get_ils5_rwy_end()              { return current_ils5->rwy_end; }
char * airport::get_ils5_type()                 { return current_ils5->type; }
char * airport::get_ils5_marker_type()          { return current_ils5->marker_type;}
char * airport::get_ils5_status()               { return current_ils5->status; }
char * airport::get_ils5_eff_date()             { return current_ils5->eff_date; }
char * airport::get_ils5_lat_ant()              { return current_ils5->lat_ant; }
char * airport::get_ils5_lat_ant_seconds()      { return current_ils5->lat_ant_seconds; }
char * airport::get_ils5_lon_ant()              { return current_ils5->lon_ant; }
char * airport::get_ils5_lon_ant_seconds()      { return current_ils5->lon_ant_seconds; }
char * airport::get_ils5_lat_lon_code()         { return current_ils5->lat_lon_code; }
char * airport::get_ils5_dist_frm_app_end()     { return current_ils5->dist_frm_app_end; }
char * airport::get_ils5_dist_frm_rnwy_cl()     { return current_ils5->dist_frm_rnwy_cl; }
char * airport::get_ils5_dir_of_ant_frm_rnwy()  { return current_ils5->dir_of_ant_frm_rnwy; }
char * airport::get_ils5_src_dist_info()        { return current_ils5->src_dist_info; }
char * airport::get_ils5_elev()                 { return current_ils5->elev; }
char * airport::get_ils5_fac_type()             { return current_ils5->fac_type; }
char * airport::get_ils5_loc_id()               { return current_ils5->loc_id; }
char * airport::get_ils5_name()                 { return current_ils5->name; }
char * airport::get_ils5_freq()                 { return current_ils5->freq; }
char * airport::get_ils5_navaid_type()          { return current_ils5->navaid_type; }
char * airport::get_ils5_low_ndb_status()       { return current_ils5->low_ndb_status; }
char * airport::get_ils5_serv_provided()        { return current_ils5->serv_provided; }

/// ILS6  /// REMARKS
char * airport::get_ils6_lfsn()       { return current_ils6->lfsn; }
char * airport::get_ils6_rwy_end()    { return current_ils6->rwy_end; }
char * airport::get_ils6_type()       { return current_ils6->type; }
char * airport::get_ils6_remarks()    { return current_ils6->remarks; }

void airport::process_airport_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->landing_facility_site_number,11,3);  //L AN 0011 00004  DLID    LANDING FACILITY SITE NUMBER
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->landing_facility_type,13,14);        //L AN 0013 00015  DLID    LANDING FACILITY TYPE
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->location_identifier,4,27);           //L AN 0004 00028  E7      LOCATION IDENTIFIER
  if (current_apt->location_identifier[3] == ' ') current_apt->location_identifier[3] = '\0';     //squelch blank character in fourth position (indexing/lookup)

  printf("locatin_identifier [%s] ",current_apt->location_identifier);

  set_field((char *)&NASRairportbuffer,(char *)&current_apt->information_effective_date,10,31);   //L AN 0010 00032  N/A     INFORMATION EFFECTIVE DATE (MM/DD/YYYY) COINCIDES WITH 56-DAY CHARTING AND PUBLICATION CYCLE DATE
  /// DEMOGRAPHIC DATA
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->faa_region_code,3,41);               //L AN 0003 00042  A6      FAA REGION CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->faa_district_office,4,44);           //L AN 0004 00045  A6A     FAA DISTRICT OR FIELD OFFICE CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->st,2,48);                            //L AN 0002 00049  A4      ASSOCIATED STATE POST OFFICE CODE
  if (current_apt->st[0] == ' ') {  current_apt->st[0]= current_apt->st[1] = 'X'; current_apt->st[2]='\0';  }
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->stname,20,50);                       //L AN 0020 00051  A4      ASSOCIATED STATE NAME
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->county,21,70);                       //L AN 0021 00071  A5      ASSOCIATED COUNTY (OR PARISH) NAME
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->county_st,2,91);                     //L AN 0002 00092  A5      ASSOCIATED COUNTY'S STATE (POST OFFICE CODE)
  set_field_no_trailing_blank((char *)&NASRairportbuffer,(char *)&current_apt->city,40,93);       //L AN 0040 00094  A1      ASSOCIATED CITY NAME
  safe_line((char *) &current_apt->city);
  set_field_no_trailing_blank((char *)&NASRairportbuffer,(char *)&current_apt->name,50,133);      //L AN 0050 00134  A2      OFFICIAL FACILITY NAME  (EX. CHICAGO O'HARE INTL)
  safe_line((char *) &current_apt->name);
  printf("official facility name [%s]\n",current_apt->name);
  /// OWNERSHIP DATA
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->ownership_type,2,183);               //L AN 0002 00184  A10     AIRPORT OWNERSHIP TYPE  PU - PUBLICLY OWNED PR - PRIVATELY OWNED MA - AIR FORCE OWNED MN - NAVY OWNED MR - ARMY OWNED CG - COAST GUARD OWNED
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->facility_use,2,185);                 //L AN 0002 00186  A18     FACILITY USE PU - OPEN TO THE PUBLIC PR - PRIVATE
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->own_name,35,187);                    //L AN 0035 00188  A11     FACILITY OWNER'S NAME
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->own_addr,72,222);                    //L AN 0072 00223  A12     OWNER'S ADDRESS
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->own_city,45,294);                    //L AN 0045 00295  A12A    OWNER'S CITY, STATE AND ZIP CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->own_phone,16,339);                   //R AN 0016 00340  A13     OWNER'S PHONE NUMBER
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->mgr_name,35,355);                    //L AN 0035 00356  A14     FACILITY MANAGER'S NAME
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->mgr_addr,72,390);                    //L AN 0072 00391  A15     MANAGER'S ADDRESS
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->mgr_city,45,462);                    //L AN 0045 00463  A15A    MANAGER'S CITY, STATE AND ZIP CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->mgr_phone,16,507);                   //R AN 0016 00508  A16     MANAGER'S PHONE NUMBE
  /// GEOGRAPHIC DATA
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_latitude_formatted,15,523);  //L AN 0015 00524  A19     AIRPORT REFERENCE POINT LATITUDE (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_latitude_seconds,12,538);    //L AN 0012 00539  A19S    AIRPORT REFERENCE POINT LATITUDE (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_longitude_formatted,15,550); //L AN 0015 00551  A20     AIRPORT REFERENCE POINT LONGITUDE (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_longitude_seconds,12,565);   //L AN 0012 00566  A20S    AIRPORT REFERENCE POINT LONGITUDE (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_ref_determ_method,1,577);    //L AN 0001 00578  A19A    AIRPORT REFERENCE POINT DETERMINATION METHOD
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_elevation,7,578);            //R AN 0007 00579  A21     AIRPORT ELEVATION  (NEAREST TENTH OF A FOOT MSL)
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_elevation_method,1,585);     //L AN 0001 00586  A21     AIRPORT ELEVATION DETERMINATION METHOD
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_mag_var,3,586);              //L AN 0003 00587  E28     MAGNETIC VARIATION AND DIRECTION
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_mag_var_epoch_yr,4,589);     //L AN 0004 00590  E28     MAGNETIC VARIATION EPOCH YEAR
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->traffic_pattern_altitude,4,593);     //R AN 0004 00594  E147    TRAFFIC PATTERN ALTITUDE  (WHOLE FEET AGL)
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->section_chart,30,597);               //L AN 0030 00598  A7      AERONAUTICAL SECTIONAL CHART ON WHICH FACILITY
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->dist_from_business,2,627);           //L AN 0002 00628  A3      DISTANCE FROM CENTRAL BUSINESS DISTRICT OF
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->dir_from_business,3,629);            //L AN 0003 00630  A3      DIRECTION OF AIRPORT FROM CENTRAL BUSINESS
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->land_area,5,632);                    //R AN 0005 00633  A22     LAND AREA COVERED BY AIRPORT (ACRES)
  /// FAA SERVICES
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->boundary_artcc,4,637);               //L AN 0004 00638  E146A   BOUNDARY ARTCC IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->boundary_artcc_faa,3,641);           //L AN 0003 00642  E146B   BOUNDARY ARTCC (FAA) COMPUTER IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->boundary_artcc_name,30,644);         //L AN 0030 00645  E146C   BOUNDARY ARTCC NAME
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->resp_artcc_rep_id,4,674);            //L AN 0004 00675  E156A   RESPONSIBLE ARTCC IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->resp_artcc_faa,3,678);               //L AN 0003 00679  E156B   RESPONSIBLE ARTCC (FAA) COMPUTER IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->resp_artcc_name,30,681);             //L AN 0030 00682  E156C   RESPONSIBLE ARTCC NAME
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->tie_in_phys,1,711);                  //L AN 0001 00712  A87     TIE-IN FSS PHYSICALLY LOCATED ON FACILITY
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->tie_in_id,4,712);                    //L AN 0004 00713  A86     TIE-IN FLIGHT SERVICE STATION (FSS) IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->tie_in_name,30,716);                 //L AN 0030 00717  A86     TIE-IN FSS NAME
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->local_phone,16,746);                 //L AN 0016 00747  A88     LOCAL PHONE NUMBER FROM AIRPORT TO FSS FOR ADMINISTRATIVE SERVICES
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->toll_free_phone,16,762);             //L AN 0016 00763  A89     TOLL FREE PHONE NUMBER FROM AIRPORT TO FSS FOR PILOT BRIEFING SERVICES
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->alt_fss_id,4,778);                   //L AN 0004 00779  A86A    ALTERNATE FSS IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->alt_fss_name,30,782);                //L AN 0030 00783  A86A    ALTERNATE FSS NAME
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->alt_fss_toll_free,16,812);           //L AN 0016 00813  E3A     TOLL FREE PHONE NUMBER FROM AIRPORT TO ALTERNATE FSS FOR PILOT BRIEFING SERVICES
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->notam_id,4,828);                     //L AN 0004 00829  E2B     IDENTIFIER OF THE FACILITY RESPONSIBLE FOR ISSUING NOTICES TO AIRMEN (NOTAMS) AND WEATHER INFORMATION FOR THE AIRPORT
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->notam_available,1,832);              //L AN 0001 00833  E139    AVAILABILITY OF NOTAM 'D' SERVICE AT AIRPORT
  /// FEDERAL STATUS
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_activ_data,7,833);           //L AN 0007 00834  E157    AIRPORT ACTIVATION DATE (MM/YYYY)
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_status_code,2,840);          //L AN 0002 00841  N/A     AIRPORT STATUS CODE CI - CLOSED INDEFINITELY CP - CLOSED PERMANENTLY O  - OPERATIONAL
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_arf_cert,15,843);            //L AN 0015 00843  A26     AIRPORT ARFF CERTIFICATION TYPE AND DATE
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->NPIAS_FEDERAL_code,7,857);           //L AN 0007 00858  A25     NPIAS/FEDERAL AGREEMENTS CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_airspace_analysis,13,864);   //L AN 0013 00865  E111    AIRPORT AIRSPACE ANALYSIS DETERMINATION
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_customs_poe,1,877);          //L AN 0001 00878  E79     FACILITY HAS BEEN DESIGNATED BY THE U.S. DEPARTMENT OF HOMELAND SECURITY AS AN INTERNATIONAL AIRPORT OF  ENTRY FOR CUSTOMS
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_customs_landing,1,878);      //L AN 0001 00879  E80     FACILITY HAS BEEN DESIGNATED BY THE U.S. DEPARTMENT OF HOMELAND SECURITY AS A CUSTOMS LANDING RIGHTS  AIRPORT.
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->military_civil_joint_use,1,879);     //L AN 0001 00880  E115    FACILITY HAS MILITARY/CIVIL JOINT USE AGREEMENT
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->military_landing_rights,1,880);      //L AN 0001 00881  E116    AIRPORT HAS ENTERED INTO AN AGREEMENT THAT GRANTS LANDING RIGHTS TO THE MILITARY
      ///AIRPORT INSPECTION DATA
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_insp_method,2,881);          //L AN 0002 00882  E155    AIRPORT INSPECTION METHOD
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_insp_agency,1,883);          //L AN 0001 00884  A111    AGENCY/GROUP PERFORMING PHYSICAL INSPECTION
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_last_inspect,8,884);         //L AN 0008 00885  A112    LAST PHYSICAL INSPECTION DATE (MMDDYYYY)
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_last_info_req,8,892);        //L AN 0008 00893  A113    LAST DATE INFORMATION REQUEST WAS COMPLETED BY FACILITY OWNER OR MANAGER  (MMDDYYYY)
      /// AIRPORT SERVICES
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->fuel_types,40,900);                  //L AN 0040 00901  A70     FUEL TYPES AVAILABLE FOR PUBLIC USE AT THE AIRPORT. THERE CAN BE UP TO 8 OCCURENCES OF A FIXED 5 CHARACTER FIELD.
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airframe_repair,5,940);              //L AN 0005 00941  A71     AIRFRAME REPAIR SERVICE AVAILABILITY/TYPE MAJOR MINOR NONE
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->powerplant_repair,5,945);            //L AN 0005 00946  A72     POWER PLANT (ENGINE) REPAIR AVAILABILITY/TYPE MAJOR MINOR NONE
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->bottled_oxy,8,950);                  //L AN 0008 00951  A73     TYPE OF BOTTLED OXYGEN AVAILABLE (VALUE REPRESENTS HIGH AND/OR LOW PRESSURE REPLACEMENT BOTTLE) HIGH LOW HIGH/LOW  NONE
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->bulk_oxy,8,958);                     //L AN 0008 00959  A74     TYPE OF BULK OXYGEN AVAILABLE (VALUE REPRESENTS HIGH AND/OR LOW PRESSURE CYLINDERS) HIGH LOW HIGH/LOW  NONE
      /// AIRPORT FACILITIES
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->light_sched,7,966);                  //L AN 0007 00967  A81     AIRPORT LIGHTING SCHEDULE
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->beacon_light_sched,7,973);           //L AN 0007 00974  A81     BEACON LIGHTING SCHEDULE
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_has_tower,1,980);            //L AN 0001 00981  A85     AIR TRAFFIC CONTROL TOWER LOCATED ON AIRPORT
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->unicom,7,981);                       //L AN 0007 00982  A82     UNICOM FREQUENCY AVAILABLE AT THE AIRPORT
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->ctaf,7,988);                         //L AN 0007 00989  E100    COMMON TRAFFIC ADVISORY FREQUENCY (CTAF)
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->segment_circle_marker,4,995);        //L AN 0004 00996  A84     SEGMENTED CIRCLE AIRPORT MARKER SYSTEM ON THE AIRPORT Y - YES N - NO NONE Y-L - YES, LIGHTED
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->lens_color,3,999);                   //L AN 0003 01000  A80     LENS COLOR OF OPERABLE BEACON LOCATED ON THE AIRPORT
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->landing_fee,2,1002);                 //L AN 0001 01003  A24     LANDING FEE CHARGED TO NON-COMMERCIAL USERS OF
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->medical_use,1,1003);                 //L AN 0001 01004  NONE    A "Y" IN THIS FIELD INDICATES THAT THE LANDING FACILITY IS USED FOR MEDICAL PURPOSES
      /// BASED AIRCRAFT
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->sega,3,1004);                        //R  N 0003 01005  A90     SINGLE ENGINE GENERAL AVIATION AIRCRAFT
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->mega,3,1007);                        //R  N 0003 01008  A91     MULTI ENGINE GENERAL AVIATION AIRCRAFT
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->jetga,3,1010);                       //R  N 0003 01011  A92     JET ENGINE GENERAL AVIATION AIRCRAFT
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->gaheli,3,1013);                      //R  N 0003 01014  A93     GENERAL AVIATION HELICOPTER
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->glider,3,1016);                      //R  N 0003 01017  A94     OPERATIONAL GLIDERS
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->military,3,1019);                    //R  N 0003 01020  A95     OPERATIONAL MILITARY AIRCRAFT (INCLUDING HELICOPTERS)
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->ultralight,3,1022);                  //R  N 0003 01023  A96     ULTRALIGHT AIRCRAFT
      /// ANNUAL OPERATIONS
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->cab_carriers,6,1025);                //R  N 0006 01026  A100    COMMERCIAL SERVICES SCHEDULED OPERATIONS BY CAB-CERTIFICATED CARRIERS OR INTRASTATE CARRIERS
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->commuter,6,1031);                    //R  N 0006 01032  A101    COMMUTER SERVICES SCHEDULED COMMUTER/CARGO CARRIERS
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->air_taxi,6,1037);                    //R  N 0006 01038  A102    AIR TAXI AIR TAXI OPERATORS CARRYING PASSENGERS, MAIL, OR MAIL FOR REVENUE
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->ga_ops,6,1043);                      //R  N 0006 01044  A103    GENERAL AVIATION LOCAL OPERATIONS THOSE OPERATING IN THE LOCAL TRAFFIC PATTERN OR WITHIN A 20-MILE RADIUS OF THE AIRPORT
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->ga_itinerant,6,1049);                //R  N 0006 01050  A104    GENERAL AVIATION ITINERANT OPERATIONS THOSE GENERAL AVIATION OPERATIONS (EXCLUDING COMMUTER OR AIR TAXI) NOT QUALIFYING AS LOCAL
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->mil_ops,6,1055);                     //R  N 0006 01056  A105    MILITARY AIRCRAFT OPERATIONS
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->ending_date,10,1061);                //L AN 0010 01062  NONE    12-MONTH ENDING DATE ON WHICH ANNUAL OPERATIONS DATA IN ABOVE SIX FIELDS IS BASED (MM/DD/YYYY)
      /// ADDITIONAL AIRPORT DATA
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->pos_source,16,1071);                 //L AN 0016 01072  NONE    AIRPORT POSITION SOURCE
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->pos_source_date,10,1087);            //L AN 0010 01088  NONE    AIRPORT POSITION SOURCE DATE (MM/DD/YYYY)
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->apt_elev_source,16,1097);            //L AN 0016 01098  NONE    AIRPORT ELEVATION SOURCE
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->apt_elev_source_date,10,1113);       //L AN 0010 01114  NONE    AIRPORT ELEVATION SOURCE DATE (MM/DD/YYYY)
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->contract_fuel,1,1123);               //L AN 0001 01124  NONE    CONTRACT FUEL AVAILABLE Y - YES N - NO
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->transient_store,12,1124);            //L AN 0012 01125  A75     TRANSIENT STORAGE FACILITIES A COMMA-SEPARATED LIST OF TRANSIENT STORAGE FACILITY TYPES AVAILABLE AT THE AIRPORT.
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->other_ac_services,70,1136);          //L AN 0071 01137  A76     OTHER AIRPORT SERVICES AVAILABLE A COMMA-SEPARATED LIST OF OTHER AIRPORT SERVICES AVAILABLE AT THE AIRPORT, WHICH INCLUDE:
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->wind_indicator,3,1207);              //L AN 0003 01208  A83     WIND INDICATOR SHOWS WHETHER A WIND INDICATOR EXISTS AT THE AIRPORT
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->airport_official_icao,7,1210);       //L AN 0007 01211  NONE    ICAO IDENTIFIER INTERNATIONAL CODING FOR AIRPORT
  set_field((char *)&NASRairportbuffer,(char *)&current_apt->min_op_network,1,1217);              //L AN 0001 01218  NONE    MINIMUM OPERATIONAL NETWORK(MON)
}

void airport::process_attendance_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_att->att_lfsn,11,3);      //L AN 0011 00004  N/A     LANDING FACILITY SITE NUMBER
  set_field((char *)&NASRairportbuffer,(char *)&current_att->att_st,2,14);        //L AN 0002 00015  N/A     LANDING FACILITY STATE POST OFFICE CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_att->att_sn,2,16);        //R AN 0002 00017  N/A     ATTENDANCE SCHEDULE SEQUENCE NUMBER A NUMBER WHICH, TOGETHER WITH THE
  set_field((char *)&NASRairportbuffer,(char *)&current_att->att_sched,108,18);   //L AN 0108 00019  A17     AIRPORT ATTENDANCE SCHEDULE (WHEN MINIMUM SERVICES ARE AVAILABLE)
}

void airport::process_runway_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->rwlanding_facility_site_number,11,4);//L AN 0011 00004  DLID    LANDING FACILITY SITE NUMBER
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->rw_st,2,14);                         //L AN 0002 00015  DLID    RUNWAY STATE POST OFFICE CODE
  set_field_no_trailing_blank((char *)&NASRairportbuffer,(char *)&current_rwy->runway_id,7,16);   //L AN 0007 00017  A30     RUNWAY IDENTIFICATION
  replace_forward_slash_with_under_score(current_rwy->runway_id);
  /// COMMON RUNWAY DATA
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->runway_length,5,23);                 //R AN 0005 00024  A31     PHYSICAL RUNWAY LENGTH (NEAREST FOOT)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->runway_width,4,28);                  //R AN 0004 00029  A32     PHYSICAL RUNWAY WIDTH (NEAREST FOOT)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->runway_surface_type_cond,12,32);     //L AN 0012 00033  A33     RUNWAY SURFACE TYPE AND CONDITION
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->runway_surface_treatment,5,44);      //L AN 0005 00045  A34     RUNWAY SURFACE TREATMENT
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->runway_pcn,11,49);                   //L AN 0011 00050  A39     PAVEMENT CLASSIFICATION NUMBER (PCN)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->runway_light_edge_intensity,5,60);   //L AN 0005 00061  A40     RUNWAY LIGHTS EDGE INTENSITY
  /// BASE END
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_id,3,65);                          //L AN 0003 00066  A30A    BASE END IDENTIFIER
  if (current_rwy->b_id[0] == ' ') current_rwy->b_id[0] = '\0';
  if (current_rwy->b_id[1] == ' ') current_rwy->b_id[1] = '\0';
  if (current_rwy->b_id[2] == ' ') current_rwy->b_id[2] = '\0';
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_true_alignment,3,68);              //L AN 0003 00069  E46     RUNWAY END TRUE ALIGNMENT
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_ils_type,10,71);                   //L AN 0010 00072  I22     INSTRUMENT LANDING SYSTEM (ILS) TYPE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_rh_traffic,1,81);                  //L AN 0001 00082  A23     RIGHT HAND TRAFFIC PATTERN FOR LANDING AIRCRAFT
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_rwy_markings,5,82);                //L AN 0005 00083  A42     RUNWAY MARKINGS  (TYPE)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_rwy_condition,1,87);               //L AN 0001 00088  A42     RUNWAY MARKINGS  (CONDITION)
  /// BASE END GEOGRAPHIC DATA
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_latitude,15,89);                   //L AN 0015 00089  E68     LATITUDE OF PHYSICAL RUNWAY END (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_latitude_seconds,12,103);          //L AN 0012 00104  E68S    LATITUDE OF PHYSICAL RUNWAY END (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_longitude,15,115);                 //L AN 0015 00116  E69     LONGITUDE OF PHYSICAL RUNWAY END (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_longitude_seconds,12,130);         //L AN 0012 00131  E69S    LONGITUDE OF PHYSICAL RUNWAY END (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_elevation,7,142);                  //R AN 0007 00143  E70     ELEVATION (FEET MSL) AT PHYSICAL RUNWAY END
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_threshold_xheight,3,149);          //R AN 0003 00150  A44     THRESHOLD CROSSING HEIGHT (FEET AGL)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_glide_slope,4,152);                //L AN 0004 00153  A45     VISUAL GLIDE PATH ANGLE (HUNDREDTHS OF DEGREES)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_dt_latitude,15,156);               //L AN 0015 00157  E161    LATITUDE  AT DISPLACED THRESHOLD (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_dt_latitude_seconds,12,171);       //L AN 0012 00172  E161S   LATITUDE  AT DISPLACED THRESHOLD (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_dt_longitude,15,183);              //L AN 0015 00184  E162    LONGITUDE AT DISPLACED THRESHOLD (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_dt_longitude_seconds,12,198);      //L AN 0012 00199  E162S   LONGITUDE AT DISPLACED THRESHOLD (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_dt_elevation,7,210);               //R AN 0007 00211  E160    ELEVATION AT DISPLACED THRESHOLD (FEET MSL)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_dt_length,4,217);                  //R AN 0004 00218  A51     DISPLACED THRESHOLD - LENGTH IN FEET FROM
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_dt_elev_at_td,7,221);              //R AN 0007 00222  E163    ELEVATION AT TOUCHDOWN ZONE (FEET MSL)
      /// BASE END LIGHTING DATA
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_glide_slope_ind,5,228);            //L AN 0005 00229  A43     VISUAL GLIDE SLOPE INDICATORS
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_rvr,3,233);                        //L AN 0003 00234  A47     RUNWAY VISUAL RANGE EQUIPMENT (RVR)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_rvv,1,236);                        //L AN 0001 00237  A47A    RUNWAY VISIBILITY VALUE EQUIPMENT (RVV)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_approach_lights,8,237);            //L AN 0008 00238  A49     APPROACH LIGHT SYSTEM
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_reil,1,245);                       //L AN 0001 00246  A48     RUNWAY END IDENTIFIER LIGHTS (REIL) AVAILABILITY
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_ctr_ln_lights,1,246);              //L AN 0001 00247  A46     RUNWAY CENTERLINE LIGHTS AVAILABILITY
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_td_lights,1,247);                  //L AN 0001 00248  A46A    RUNWAY END TOUCHDOWN LIGHTS AVAILABILITY
      /// BASE END OBJECT DATA
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_object,11,248);                    //L AN 0011 00249  A52     CONTROLLING OBJECT DESCRIPTION  (EX. TREES,BLDG,PLINE,FENCE,NONE)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_marked_lighted,4,259);             //L AN 0004 00260  A53     CONTROLLING OBJECT MARKED/LIGHTED M  - MARKED, L  - LIGHTED, ML - MARKED AND LIGHTED, NONE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_faa_cfr_77,5,263);                 //L AN 0005 00264  A50     FAA CFR PART 77 (OBJECTS AFFECTING NAVIGABLE AIRSPACE)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_clearance_slope,2,268);            //R AN 0002 00269  A57     CONTROLLING OBJECT CLEARANCE SLOPE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_height_above_rwy,5,270);           //R AN 0005 00271  A54     CONTROLLING OBJECT HEIGHT ABOVE RUNWAY
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_dist_from_rwy,5,275);              //R AN 0005 00276  A55     CONTROLLING OBJECT DISTANCE FROM RUNWAY END (FEET)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_center_line_offset,7,280);         //L AN 0007 00281  A56     CONTROLLING OBJECT CENTERLINE OFFSET
/// RECIPROCAL END
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_id,3,287);                         //L AN 0003 00288  A30A    RECIPROCAL END IDENTIFIER
  if (current_rwy->r_id[0] == ' ') current_rwy->r_id[0] = '\0';
  if (current_rwy->r_id[1] == ' ') current_rwy->r_id[1] = '\0';
  if (current_rwy->r_id[2] == ' ') current_rwy->r_id[2] = '\0';
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_true_alignment,3,290);             //L AN 0003 00291  E46     RUNWAY END TRUE ALIGNMENT
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_ils_type,10,293);                  //L AN 0010 00294  I22     INSTRUMENT LANDING SYSTEM (ILS) TYPE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_rh_traffic,1,303);                 //L AN 0001 00304  A23     RIGHT HAND TRAFFIC PATTERN FOR LANDING AIRCRAFT
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_rwy_markings,5,304);               //L AN 0005 00305  A42     RUNWAY MARKINGS  (TYPE)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_rwy_condition,1,309);              //L AN 0001 00310  A42     RUNWAY MARKINGS  (CONDITION)
      /// RECIPROCAL END GEOGRAPHIC DATA
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_latitude,15,310);                  //L AN 0015 00311  E68     LATITUDE OF PHYSICAL RUNWAY END (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_latitude_seconds,12,325);          //L AN 0012 00326  E68S    LATITUDE OF PHYSICAL RUNWAY END (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_longitude,15,337);                 //L AN 0015 00338  E69     LONGITUDE OF PHYSICAL RUNWAY END (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_longitude_seconds,12,352);         //L AN 0012 00353  E69S    LONGITUDE OF PHYSICAL RUNWAY END (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_elevation,7,364);                  //R AN 0007 00365  E70     ELEVATION (FEET MSL) AT PHYSICAL RUNWAY END
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_threshold_xheight,3,371);          //R AN 0003 00372  A44     THRESHOLD CROSSING HEIGHT (FEET AGL)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_glide_slope,4,374);                //L AN 0004 00375  A45     VISUAL GLIDE PATH ANGLE (HUNDREDTHS OF DEGREES)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_dt_latitude,15,378);               //L AN 0015 00379  E161    LATITUDE  AT DISPLACED THRESHOLD (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_dt_latitude_seconds,12,393);       //L AN 0012 00394  E161S   LATITUDE  AT DISPLACED THRESHOLD (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_dt_longitude,15,405);              //L AN 0015 00406  E162    LONGITUDE AT DISPLACED THRESHOLD (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_dt_longitude_seconds,12,420);      //L AN 0012 00421  E162S   LONGITUDE AT DISPLACED THRESHOLD (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_dt_elevation,7,432);               //R AN 0007 00433  E160    ELEVATION AT DISPLACED THRESHOLD (FEET MSL)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_dt_length,4,439);                  //R AN 0004 00440  A51     DISPLACED THRESHOLD - LENGTH IN FEET FROM
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_dt_elev_at_td,7,443);              //R AN 0007 00444  E163    ELEVATION AT TOUCHDOWN ZONE (FEET MSL)
      /// RECIPROCAL END LIGHTING DATA
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_glide_slope_ind,5,450);            //L AN 0005 00451  A43     VISUAL GLIDE SLOPE INDICATORS
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_rvr,3,455);                        //L AN 0003 00456  A47     RUNWAY VISUAL RANGE EQUIPMENT (RVR)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_rvv,1,458);                        //L AN 0001 00459  A47A    RUNWAY VISIBILITY VALUE EQUIPMENT (RVV)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_approach_lights,8,459);            //L AN 0008 00460  A49     APPROACH LIGHT SYSTEM
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_reil,1,467);                       //L AN 0001 00468  A48     RUNWAY END IDENTIFIER LIGHTS (REIL) AVAILABILITY
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_ctr_ln_lights,1,468);              //L AN 0001 00469  A46     RUNWAY CENTERLINE LIGHTS AVAILABILITY
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_td_lights,1,469);                  //L AN 0001 00470  A46A    RUNWAY END TOUCHDOWN LIGHTS AVAILABILITY
      /// RECIPROCAL END OBJECT DATA
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_object,11,470);                    //L AN 0011 00471  A52     CONTROLLING OBJECT DESCRIPTION
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_marked_lighted,4,481);             //L AN 0004 00482  A53     CONTROLLING OBJECT MARKED/LIGHTED
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_faa_cfr_77,5,485);                 //L AN 0005 00486  A50     FAA CFR PART 77 (OBJECTS AFFECTING NAVIGABLE AIRSPACE)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_clearance_slope,2,490);            //R AN 0002 00491  A57     CONTROLLING OBJECT CLEARANCE SLOPE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_height_above_rwy,5,492);           //R AN 0005 00493  A54     CONTROLLING OBJECT HEIGHT ABOVE RUNWAY
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_dist_from_rwy,5,497);              //R AN 0005 00498  A55     CONTROLLING OBJECT DISTANCE FROM RUNWAY END
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_center_line_offset,7,502);         //L AN 0007 00503  A56     CONTROLLING OBJECT CENTERLINE OFFSET
      ///ADDITIONAL COMMON RUNWAY DATA
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->length_src,16,509);                  //L AN 0016 00510  NONE    RUNWAY LENGTH SOURCE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->length_date,10,525);                 //L AN 0010 00526  NONE    RUNWAY LENGTH SOURCE DATE (MM/DD/YYYY)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->single_wheel_cap,6,535);             //R AN 0006 00536  A35     RUNWAY WEIGHT-BEARING CAPACITY FOR Single wheel type landing gear (DC3), (C47), (F15), etc.
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->dual_wheel_cap,6,541);               //R AN 0006 00542  A36     RUNWAY WEIGHT-BEARING CAPACITY FOR Dual wheel type landing gear (BE1900), (B737), (A319), etc.
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->dual_wheel_tandem_cap,6,547);        //R AN 0006 00548  A37     RUNWAY WEIGHT-BEARING CAPACITY FOR Two dual wheels in tandem type landing gear (B707), etc.
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->two_duel_wheel_tandem_cap,6,553);    //R AN 0006 00554  A38     RUNWAY WEIGHT-BEARING CAPACITY FOR Two dual wheels in tandem/two dual wheels in double tandem body gear type landing gear (B747, E4).
      /// ADDITIONAL BASE END DATA
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_runway_end_gradient,5,559);        //R AN 0005 00560  E40     RUNWAY END GRADIENT
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_runway_end_gradient_dir,4,564);    //L AN 0004 00565  E40     RUNWAY END GRADIENT DIRECTION (UP OR DOWN)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_runway_end_pos_src,16,568);        //L AN 0016 00569  NONE    RUNWAY END POSITION SOURCE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_runway_end_pos_date,10,584);       //L AN 0010 00585  NONE    RUNWAY END POSITION SOURCE DATE (MM/DD/YYYY)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_runway_end_elev_src,16,594);       //L AN 0016 00595  NONE    RUNWAY END ELEVATION SOURCE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_runway_end_elev_src_date,10,610);  //L AN 0010 00611  NONE    RUNWAY END ELEVATION SOURCE DATE (MM/DD/YYYY)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_dt_pos_src,16,620);                //L AN 0016 00621  NONE    DISPLACED THESHOLD POSITION SOURCE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_dt_pos_src_date,10,636);           //L AN 0010 00637  NONE    DISPLACED THESHOLD POSITION SOURCE DATE (MM/DD/YYYY)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_dt_elev_src,16,646);               //L AN 0016 00647  NONE    DISPLACED THESHOLD ELEVATION SOURCE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_dt_elev_src_date,10,662);          //L AN 0010 00663  NONE    DISPLACED THESHOLD ELEVATION SOURCE DATE (MM/DD/YYYY)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_td_elev_src,16,672);               //L AN 0016 00673  NONE    TOUCHDOWN ZONE ELEVATION SOURCE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_td_elev_src_date,10,688);          //L AN 0010 00689  NONE    TOUCHDOWN ZONE ELEVATION SOURCE DATE (MM/DD/YYYY)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_tora,5,698);                       //R AN 0005 00699  A60     TAKEOFF RUN AVAILABLE (TORA), IN FEET
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_toda,5,703);                       //R AN 0005 00704  A61     TAKEOFF DISTANCE AVAILABLE (TODA), IN FEET
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_asda,5,708);                       //R AN 0005 00709  A62     ACLT STOP DISTANCE AVAILABLE (ASDA), IN FEET
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_lda,5,713);                        //R AN 0005 00714  A63     LANDING DISTANCE AVAILABLE (LDA), IN FEET
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_lahso,5,718);                      //R AN 0005 00719  NONE    AVAILABLE LANDING DISTANCE FOR LAND AND HOLD SHORT OPERATIONS (LAHSO)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_id_int_rw,7,723);                  //L AN 0007 00724  NONE    ID OF INTERSECTING RUNWAY DEFINING HOLD SHORT POINT
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_id_desc_ent,40,730);               //L AN 0040 00731  NONE    DESCRIPTION OF ENTITY DEFINING HOLD SHORT POINT IF NOT AN INTERSECTING RUNWAY (E.G., AN INTERSECTING TAXIWAY).
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_lat_lahso,15,770);                 //L AN 0015 00771  NONE    LATITUDE OF LAHSO HOLD SHORT POINT (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_lat_lahso_seconds,12,785);         //L AN 0012 00786  NONE    LATITUDE OF LAHSO HOLD SHORT POINT (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_lon_lahso,15,797);                 //L AN 0015 00798  NONE    LONGITUDE OF LAHSO HOLD SHORT POINT (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_lon_lahso_seconds,12,812);         //L AN 0012 00813  NONE    LONGITUDE OF LAHSO HOLD SHORT POINT (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_latlon_lahso_src,16,824);          //L AN 0016 00825  NONE    LAHSO HOLD SHORT POINT LAT/LONG SOURCE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->b_latlon_lahso_src_date,10,840);     //L AN 0010 00841  NONE    HOLD SHORT POINT LAT/LONG SOURCE DATE (MM/DD/YYYY)
      /// ADDITIONAL RECIPROCAL END DATA
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_runway_end_gradient,5,850);        //R AN 0005 00851  E40     RUNWAY END GRADIENT
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_runway_end_gradient_dir,4,855);    //L AN 0004 00856  E40     RUNWAY END GRADIENT DIRECTION (UP OR DOWN)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_runway_end_pos_src,16,859);        //L AN 0016 00860  NONE    RUNWAY END POSITION SOURCE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_runway_end_pos_date,10,875);       //L AN 0010 00876  NONE    RUNWAY END POSITION SOURCE DATE (MM/DD/YYYY)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_runway_end_elev_src,16,885);       //L AN 0016 00886  NONE    RUNWAY END ELEVATION SOURCE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_runway_end_elev_src_date,10,901);  //L AN 0010 00902  NONE    RUNWAY END ELEVATION SOURCE DATE (MM/DD/YYYY)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_dt_pos_src,16,911);                //L AN 0016 00912  NONE    DISPLACED THESHOLD POSITION SOURCE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_dt_pos_src_date,10,927);           //L AN 0010 00928  NONE    DISPLACED THESHOLD POSITION SOURCE DATE (MM/DD/YYYY)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_dt_elev_src,16,937);               //L AN 0016 00938  NONE    DISPLACED THESHOLD ELEVATION SOURCE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_dt_elev_src_date,10,953);          //L AN 0010 00954  NONE    DISPLACED THESHOLD ELEVATION SOURCE DATE (MM/DD/YYYY)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_td_elev_src,16,963);               //L AN 0016 00964  NONE    TOUCHDOWN ZONE ELEVATION SOURCE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_td_elev_src_date,10,879);          //L AN 0010 00980  NONE    TOUCHDOWN ZONE ELEVATION SOURCE DATE (MM/DD/YYYY)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_tora,5,989);                       //R AN 0005 00990  A60     TAKEOFF RUN AVAILABLE (TORA), IN FEET
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_toda,5,994);                       //R AN 0005 00995  A61     TAKEOFF DISTANCE AVAILABLE (TODA), IN FEET
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_asda,5,999);                       //R AN 0005 01000  A62     ACLT STOP DISTANCE AVAILABLE (ASDA), IN FEET
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_lda,5,1004);                       //R AN 0005 01005  A63     LANDING DISTANCE AVAILABLE (LDA), IN FEET
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_lahso,5,1009);                     //R AN 0005 01010  NONE    AVAILABLE LANDING DISTANCE FOR LAND AND HOLD SHORT OPERATIONS (LAHSO)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_id_int_rw,7,1014);                 //L AN 0007 01015  NONE    ID OF INTERSECTING RUNWAY DEFINING HOLD SHORT POINT
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_id_desc_ent,40,1021);              //L AN 0040 01022  NONE    DESCRIPTION OF ENTITY DEFINING HOLD SHORT POINT IF NOT AN INTERSECTING RUNWAY (E.G., AN INTERSECTING TAXIWAY).
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_lat_lahso,15,1061);                //L AN 0015 01062  NONE    LATITUDE OF LAHSO HOLD SHORT POINT (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_lat_lahso_seconds,12,1076);        //L AN 0012 01077  NONE    LATITUDE OF LAHSO HOLD SHORT POINT (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_lon_lahso,15,1088);                //L AN 0015 01089  NONE    LONGITUDE OF LAHSO HOLD SHORT POINT (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_lon_lahso_seconds,12,1103);        //L AN 0012 01104  NONE    LONGITUDE OF LAHSO HOLD SHORT POINT (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_latlon_lahso_src,16,1115);         //L AN 0016 01116  NONE    LAHSO HOLD SHORT POINT LAT/LONG SOURCE
  set_field((char *)&NASRairportbuffer,(char *)&current_rwy->r_latlon_lahso_src_date,10,1131);    //L AN 0010 01132  NONE    HOLD SHORT POINT LAT/LONG SOURCE DATE (MM/DD/YYYY)
}

void airport::process_arrest_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_ars->ars_lfsn,11,3);            //L AN 0011 00004  N/A     LANDING FACILITY SITE NUMBER
  set_field((char *)&NASRairportbuffer,(char *)&current_ars->ars_lfst,2,14);            //L AN 0002 00015  N/A     LANDING FACILITY STATE POST OFFICE CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_ars->ars_runway,7,16);          //L AN 0007 00017  A30     RUNWAY IDENTIFICATION
  set_field((char *)&NASRairportbuffer,(char *)&current_ars->ars_runway_end,3,23);      //L AN 0003 00024  A30A    RUNWAY END IDENTIFIER THE RUNWAY END DESCRIBED BY THE ARRESTING SYSTEM INFORMATION.
  set_field((char *)&NASRairportbuffer,(char *)&current_ars->ars_type,9,26);            //L AN 0009 00027  E60     TYPE OF AIRCRAFT ARRESTING DEVICE INDICATES TYPE OF JET ARRESTING BARRIER INSTALLED AT THE FAR END.
}

void airport::process_remark_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_rmk->rmk_lfsn,11,3);            //L AN 0011 00004  N/A     LANDING FACILITY SITE NUMBER
  set_field((char *)&NASRairportbuffer,(char *)&current_rmk->rmk_lfst,2,14);            //L AN 0002 00015  N/A     LANDING FACILITY STATE POST OFFICE CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_rmk->rmk_name,15,16);           //L AN 0015 00017  N/A     REMARK ELEMENT NAME THIS INFORMATION RELATES A REMARK TO ONE OF THE PREVIOUSLY DESCRIBED DATA ELEMENTS.
  set_field((char *)&NASRairportbuffer,(char *)&current_rmk->rmk_text,1500,31);         //L AN 1500 00032  N/A     REMARK TEXT FREE FORM TEXT THAT FURTHER DESCRIBES A SPECIFIC INFORMATION ITEM OR MAY BE GENERAL IN NATURE.
}

void airport::process_twr1_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->term_com_fac_id,4,4);          // L AN 0004 00005  DLID    TERMINAL COMMUNICATIONS FACILITY IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->info_effect_date,10,8);        // L AN 0010 00009  NONE    INFORMATION EFFECTIVE DATE (MM/DD/YYYY)
      /// Landing Facility(Airport) Data                //
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->lfsn,11,18);                   // L AN 0011 00019  DLID    LANDING FACILITY SITE NUMBER
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->faa_reg_code,3,29);            // L AN 0003 00030  A6      FAA REGION CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->assoc_st_name,30,32);          // L AN 0030 00033  A4      ASSOCIATED STATE NAME
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->assoc_st,2,62);                // L AN 0002 00063  A4      ASSOCIATED STATE POST OFFICE  CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->assoc_city_name,40,64);        // L AN 0040 00065  A1      ASSOCIATED CITY NAME
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->offic_apt_name,50,104);        // L AN 0050 00105  A2      OFFICIAL AIRPORT NAME
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->latitude,14,154);              // L AN 0014 00155  A19     AIRPORT REFERENCE POINT LATITUDE (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->latitude_seconds,11,168);      // L AN 0011 00169  A19S    AIRPORT REFERENCE POINT LATITUDE (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->longitude,14,179);             // L AN 0014 00180  A20     AIRPORT REFERENCE POINT LONGITUDE (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->longitude_seconds,11,193);     // L AN 0011 00194  A20S    AIRPORT REFERENCE POINT LONGITUDE (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->tie_in_fss,4,204);             // L AN 0004 00205  A86     TIE-IN FLIGHT SERVICE STATION (FSS) IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->tie_in_fss_name,30,208);       // L AN 0030 00209  A86     TIE-IN FLIGHT SERVICE STATION (FSS) NAME
      /// Terminal Communications Facility Data         //
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->fac_type,12,238);               // L AN 0012 00239  TA9     FACILITY TYPE
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->num_hours,2,250);               // L AN 0002 00251  TA55    NUMBER OF HOURS OF DAILY OPERATION
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->num_hours_code,3,252);          // L AN 0003 00253  TA55    NUMBER OF HOURS OF DAILY OPERATION
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->master_apt_id,4,255);           // L AN 0004 00256  TA34    MASTER AIRPORT LOCATION IDENTIFIER (EX: LAX)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->master_apt_name,50,259);        // L AN 0050 00260  TA34    NAME OF MASTER AIRPORT FURNISHING SERVICES
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->dir_find_eq,15,309);            // L AN 0015 00310  TA38    DIRECTION FINDING EQUIPMENT (TYPE)
      /// Terminal Communications Facility Off Airport  //
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->assoc_land_fac,50,324);         // L AN 0050 00325  TA45    NAME OF ASSOCIATED LANDING FACILITY WHEN THE
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->accoc_city,40,374);             // L AN 0040 00375  TA46    NAME OF THE ASSOCIATED CITY WHEN THE FACILITY
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->st_prov,20,414);                // L AN 0020 00415  TA47    NAME OF THE STATE OR PROVINCE WHEN THE FACILITY
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->st_county,25,434);              // L AN 0025 00435  TA48    NAME OF STATE/COUNTRY WHEN FACILITY NOT LOCATED
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->country_st,2,459);              // L AN 0002 00460  TA48    COUNTRY/STATE  POST OFFICE CODE WHEN FACILITY
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->faa_reg_code_off_apt,3,461);    // L AN 0003 00462  TA49    FAA REGION CODE WHEN THE FACILITY NOT LOCATED
      /// latitude/longitude data                       //
         /// airport surveillance radar                 //
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->as_rad_lat,14,464);             // L AN 0014 00465  TA32    AIRPORT SURVEILLANCE RADAR LATITUDE(FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->as_rad_lat_seconds,11,478);     // L AN 0011 00479  TA32    AIRPORT SURVEILLANCE RADAR LATITUDE (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->as_rad_lon,14,489);             // L AN 0014 00490  TA33    AIRPORT SURVEILLANCE RADAR LONGITUDE (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->as_rad_lon_seconds,11,503);     // L AN 0011 00504  TA33    AIRPORT SURVEILLANCE RADAR LONGITUDE (SECONDS)
         /// direction finding antenna                  //
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->dfa_rad_lat,14,514);            // L AN 0014 00515  TA39    LATITUDE OF DIRECTION FINDING ANTENNA (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->dfa_rad_lat_seconds,11,528);    // L AN 0011 00529  TA39    LATITUDE OF DIRECTION FINDING ANTENNA (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->dfa_rad_lon,14,539);            // L AN 0014 00540  TA40    LONGITUDE OF DIRECTION FINDING ANTENNA(FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->dfa_rad_lon_seconds,11,553);    // L AN 0011 00554  TA40    LONGITUDE OF DIRECTION FINDING ANTENNA (SECONDS)
      /// Operator Data                                 //
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->twr,40,564);                    // L AN 0040 00565  TA11    NAME OF THE AGENCY THAT OPERATES THE TOWER
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->mil_ops_data,40,604);           // L AN 0040 00605  TA53    NAME OF THE AGENCY THAT OPERATES MILITARY
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->p_app_cntrl,40,644);            // L AN 0040 00645  TA20    NAME OF THE AGENCY THAT OPERATES THE PRIMARY
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->s_app_cntrl,40,684);            // L AN 0040 00685  TA23    NAME OF THE AGENCY OPERATING THE SECONDARY
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->p_dep_cntrl,40,724);            // L AN 0040 00725  TA26    NAME OF THE AGENCY OPERATING THE PRIMARY
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->s_dep_cntrl,40,764);            // L AN 0040 00765  TA29    NAME OF THE AGENCY OPERATING THE SECONDARY
      /// radio call data                               //
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->pilot_to_twr,26,804);           // L AN 0026 00805  TA51    RADIO CALL USED BY PILOT TO CONTACT TOWER
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->mill_ops_call,26,830);          // L AN 0026 00831  TA52    RADIO CALL NAME FOR MILITARY OPERATIONS AT
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->p_app_cntr_call,26,856);        // L AN 0026 00857  TA19    RADIO CALL OF FACILITY THAT FURNISHES PRIMARY
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->p_take_over_cntrl_call,26,882); // L AN 0026 00883  TA22    RADIO CALL OF FACILITY THAT TAKES OVER APPROACH
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->p_dep_cntr,26,908);             // L AN 0026 00909  TA25    RADIO CALL OF FACILITY THAT FURNISHES PRIMARY
  set_field((char *)&NASRairportbuffer,(char *)&current_twr1->d_take_over_dep_cntrl,26,934);  // L AN 0026 00935  TA28    RADIO CALL OF FACILITY THAT TAKES OVER
}
void airport::process_twr2_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&twr2->ident,4,4);      // L AN 0004 00005  DLID    TERMINAL COMMUNICATIONS FACILITY IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&twr2->pmsv,200,8);     // L AN 0200 00009  TA42    HOURS OF OPERATION OF THE MILITARY
  set_field((char *)&NASRairportbuffer,(char *)&twr2->macp,200,208);   // L AN 0200 00209  TA41    HOURS OF OPERATION OF THE MILITARY
  set_field((char *)&NASRairportbuffer,(char *)&twr2->dyly,200,408);   // L AN 0200 00409  TA54    HOURS OF MILITARY OPERATIONS CONDUCTED
  set_field((char *)&NASRairportbuffer,(char *)&twr2->p_app,200,608);  // L AN 0200 00609  TA21    HOURS OF OPERATION OF PRIMARY APPROACH
  set_field((char *)&NASRairportbuffer,(char *)&twr2->s_app,200,808);  // L AN 0200 00809  TA24    HOURS OF OPERATION OF SECONDARY APPROACH
  set_field((char *)&NASRairportbuffer,(char *)&twr2->p_dep,200,1008); // L AN 0200 01009  TA27    HOURS OF OPERATION OF PRIMARY DEPARTURE
  set_field((char *)&NASRairportbuffer,(char *)&twr2->s_dep,200,1208); // L AN 0200 01209  TA30    HOURS OF OPERATION OF SECONDARY DEPARTURE
  set_field((char *)&NASRairportbuffer,(char *)&twr2->twr,200,1408);   // L AN 0200 01409  TA15    HOURS OF TOWER OPERATION IN LOCAL TIME
}
void airport::process_twr3_record()
{
/** offset details
L AN 0044 00009  TA13    FREQUENCY(S)
L AN 0050 00053  TA13    FREQUENCY USE.(1)
L AN 0044 00103  TA13    FREQUENCY(S)
L AN 0050 00147  TA13    FREQUENCY USE.(2)
L AN 0044 00197  TA13    FREQUENCY(S)
L AN 0050 00241  TA13    FREQUENCY USE.(3)
L AN 0044 00291  TA13    FREQUENCY(S)
L AN 0050 00335  TA13    FREQUENCY USE.(4)
L AN 0044 00385  TA13    FREQUENCY(S)
L AN 0050 00429  TA13    FREQUENCY USE.(5)
L AN 0044 00479  TA13    FREQUENCY(S)
L AN 0050 00523  TA13    FREQUENCY USE.(6)
L AN 0044 00573  TA13    FREQUENCY(S)
L AN 0050 00617  TA13    FREQUENCY USE.(7)
L AN 0044 00667  TA13    FREQUENCY(S)
L AN 0050 00711  TA13    FREQUENCY USE.(8)
L AN 0044 00761  TA13    FREQUENCY(S)
L AN 0050 00805  TA13    FREQUENCY USE.(9)
L AN 0060 00855  TA13    FREQUENCY(S) (1) SECTORIZATION
L AN 0060 00915  TA13    FREQUENCY(S) (2)
L AN 0060 00975  TA13    FREQUENCY(S) (3)
L AN 0060 01035  TA13    FREQUENCY(S) (4)
L AN 0060 01095  TA13    FREQUENCY(S) (5)
L AN 0060 01155  TA13    FREQUENCY(S) (6)
L AN 0060 01215  TA13    FREQUENCY(S) (7)
L AN 0060 01275  TA13    FREQUENCY(S) (8)
L AN 0060 01335  TA13    FREQUENCY(S) (9)
**/
  int offset_freq[9] = {8,102,196,290,384,478,572,666,760};
  int offset_use[9] = {52,146,240,334,428,522,616,710,804};
  int offset_trunc[9] = {854,914,974,1034,1094,1154,1214,1274,1334};
  set_field((char *)&NASRairportbuffer,(char *)&current_twr3->ident,4,4);                              // L AN 0004 00005  DLID    TERMINAL COMMUNICATIONS FACILITY IDENTIFIER
  for (int i = 0; i < 9; i++) {
    set_field((char *)&NASRairportbuffer,(char *)&current_twr3->freq[i],44,offset_freq[i]);            // L AN 0044 00009  TA13    FREQUENCY(S) FOR MASTER AIRPORT USE ONLY AND   |freq/use paired then trunc fields
    set_field((char *)&NASRairportbuffer,(char *)&current_twr3->use[i],40,offset_use[i]);              // L AN 0050 00053  TA13    FREQUENCY USE.(1)                              |
    set_field((char *)&NASRairportbuffer,(char *)&current_twr3->freq_not_trunc[i],60,offset_trunc[i]); // L AN 0060 00855  TA13    FREQUENCY(S) FOR MASTER AIRPORT USE ONLY AND
  }
}
void airport::process_twr4_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_twr4->ident,4,4);      // L AN 0004 00005  DLID    TERMINAL COMMUNICATIONS FACILITY IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_twr4->service,100,8);  // L AN 0100 00009  TA35    MASTER AIRPORT SERVICES
}
void airport::process_twr5_record()
{
/** offset details
L AN 0010 00045  TA31    TYPE OF RADAR AT THE TOWER(1)                  | paired
L AN 0200 00055  TA31    RADAR HOURS OF OPERATION(1) (EX: 0700-2300)    |
L AN 0010 00255  TA31    TYPE OF RADAR AT THE TOWER(2)
L AN 0200 00265  TA31    RADAR HOURS OF OPERATION(2)
L AN 0010 00465  TA31    TYPE OF RADAR AT THE TOWER(3)
L AN 0200 00475  TA31    RADAR HOURS OF OPERATION(3)
L AN 0010 00675  TA31    TYPE OF RADAR AT THE TOWER(4)
L AN 0200 00685  TA31    RADAR HOURS OF OPERATION(4)
**/
  int offset_twr[4] = {44,254,464,674};
  int offset_hr[4]  = {54,264,474,684};
  set_field((char *)&NASRairportbuffer,(char *)&twr5->ident,4,4);          // L AN 0004 00005  DLID    TERMINAL COMMUNICATIONS FACILITY IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&twr5->p_apr_call,9,8);     // L AN 0009 00009  TA19    /RADAR/ OR /NON-RADAR/ PRIMARY APPROACH CALL
  set_field((char *)&NASRairportbuffer,(char *)&twr5->s_app_call,9,17);    // L AN 0009 00018  TA22    /RADAR/ OR /NON-RADAR/ SECONDARY APPROACH CALL
  set_field((char *)&NASRairportbuffer,(char *)&twr5->p_dpt_call,9,26);    // L AN 0009 00027  TA25    /RADAR/ OR /NON-RADAR/ PRIMARY DEPARTURE CALL
  set_field((char *)&NASRairportbuffer,(char *)&twr5->s_dpt_call,9,35);    // L AN 0009 00036  TA28    /RADAR/ OR /NON-RADAR/ SECONDARY DEPARTURE CALL
  for (int i = 0; i < 4; i++) {
  set_field((char *)&NASRairportbuffer,(char *)&twr5->radar_type[i],10,offset_twr[i]);  // L AN 0010 00045  TA31    TYPE OF RADAR AT THE TOWER(1)                  | paired
  set_field((char *)&NASRairportbuffer,(char *)&twr5->radar_hrs[i],200,offset_hr[i]);  // L AN 0200 00055  TA31    RADAR HOURS OF OPERATION(1) (EX: 0700-2300)    |
  }
}
void airport::process_twr6_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_twr6->ident,4,4);     // L AN 0004 00005  DLID    TERMINAL COMMUNICATIONS FACILITY IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_twr6->elem_nbr,5,8);  // L AN 0005 00009  NONE    TOWER ELEMENT NUMBER
  set_field((char *)&NASRairportbuffer,(char *)&current_twr6->remark,800,13);  // L AN 0800 00014  NONE    TOWER REMARK TEXT
}
void airport::process_twr7_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->ident,4,4);           // L AN 0004 00005  DLID    TERMINAL COMMUNICATIONS FACILITY IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->sat_freq,44,8);       // L AN 0044 00009  DLID    SATELLITE FREQUENCY (EX: 126.1)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->sat_use,50,52);       // L AN 0050 00053  DLID    SATELLITE FREQUENCY USE (EX: APCH/P DEP/P)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->apt_site_nbr,11,102); // L AN 0011 00103  S6S     SATELLITE AIRPORT SITE NUMBER
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->apt_id,4,113);        // L AN 0004 00114  A7      SATELLITE AIRPORT LOCATION IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->faa_reg,3,117);       // L AN 0003 00118  A6      SATELLITE FAA REGION CODE (EX: AWP)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->st_name,30,120);      // L AN 0030 00121  A4      SATELLITE ASSOCIATED STATE NAME
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->st,2,150);            // L AN 0002 00151  A4      SATELLITE ASSOCIATED STATE POST OFFICE CODE
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->city,40,152);         // L AN 0040 00153  A1      SATELLITE ASSOCIATED CITY (EX: PALMDALE)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->arpt_name,50,192);    // L AN 0050 00193  A2      SATELLITE ARPT NAME
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->lat,14,242);          // L AN 0014 00243  A19     AIRPORT LATITUDE(FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->lat_seconds,11,256);  // L AN 0011 00257  A19S    AIRPORT LATITUDE (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->lon,14,267);          // L AN 0014 00268  A20     AIRPORT LONGITUDE (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->lon_seconds,11,281);  // L AN 0011 00282  A20S    AIRPORT LONGITUDE (SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->fss_id,4,292);        // L AN 0004 00293  A86     FLIGHT SERVICE STATION IDENTIFIER (EX: WJF)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->fss_name,30,296);     // L AN 0030 00297  A86     FLIGHT SERVICE STATION NAME
      /// Master Airport Information //
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->m_arpt_id,11,326);    // L AN 0011 00327  S021    MASTER AIRPORT INFORMATION (EX: 01526.8*A)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->m_faa_reg,3,337);     // L AN 0003 00338  A6      MASTER AIRPORT FAA REGION CODE (EX: ACE)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->m_st_name,30,340);    // L AN 0030 00341  A4      MASTER AIRPORT ASSOCIATED STATE NAME
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->m_st,3,370);          // L AN 0002 00371  A4      MASTER AIRPORT ASSOCIATED STATE POST OFFICE
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->m_city,40,372);       // L AN 0040 00373  A1      MASTER AIRPORT ASSOCIATED CITY (EX: EWARDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->m_arpt_name,50,412);  // L AN 0050 00413  A2      MASTER AIRPORT NAME  (EX: EDWARDS AFB)
  set_field((char *)&NASRairportbuffer,(char *)&current_twr7->m_sat_freq,60,462);   // L AN 0060 00463  ????    SATELLITE FREQUENCY (EX: 126.1) (NOT TRUNCATED)
}
void airport::process_twr8_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&twr8->ident,4,4);      // L AN 0004 00005  DLID    TERMINAL COMMUNICATIONS FACILITY IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&twr8->class_b,1,8);    // L AN 0001 00009  ????    CLASS B AIRSPACE (EX: Y)
  set_field((char *)&NASRairportbuffer,(char *)&twr8->class_c,1,9);    // L AN 0001 00010  ????    CLASS C AIRSPACE (EX: Y)
  set_field((char *)&NASRairportbuffer,(char *)&twr8->class_d,1,10);   // L AN 0001 00011  ????    CLASS D AIRSPACE (EX: Y)
  set_field((char *)&NASRairportbuffer,(char *)&twr8->class_e,1,11);   // L AN 0001 00012  ????    CLASS E AIRSPACE (EX: Y)
  set_field((char *)&NASRairportbuffer,(char *)&twr8->hours,300,12);   // L AN 0300 00013  ????    AIRSPACE HOURS
}
void airport::process_twr9_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_twr9->ident,4,4);      // L AN 0004 00005  DLID    TERMINAL COMMUNICATIONS FACILITY IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_twr9->sn,4,8);         // R  N 0004 00009  NONE    ATIS SERIAL NUMBER
  set_field((char *)&NASRairportbuffer,(char *)&current_twr9->hours,200,12);   // L AN 0200 00013  TA43    ATIS HOURS OF OPERATION IN LOCAL TIME
  set_field((char *)&NASRairportbuffer,(char *)&current_twr9->purpose,100,212);// L AN 0100 00213  NONE    OPTIONAL DESCRIPTION OF PURPOSE, FULFILLED BY ATIS
  set_field((char *)&NASRairportbuffer,(char *)&current_twr9->phone,18,312);   // L AN 0018 00313  NONE    ATIS PHONE NUMBER
}

void airport::process_ils1_record()
{
      /// ILS AIRPORT/RUNWAY INFORMATION
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->lfsn,11,4);              //L AN 0011 00005  DLID    AIRPORT SITE NUMBER IDENTIFIER. (EX. 04508.*A)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->rwy_end,3,15);           //L AN 0003 00016  DLID    ILS RUNWAY END IDENTIFIER. (EX: 18,36L)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->type,10,18);             //L AN 0010 00019  I22     ILS SYSTEM TYPE
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->id_code,5,28);           //L AN 0006 00029  I30     IDENTIFICATION CODE OF ILS.
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->eff_date,10,34);         //L AN 0010 00035  N/A     INFORMATION EFFECTIVE DATE (MM/DD/YYYY)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->apt_name,50,44);         //L AN 0050 00045  A2      AIRPORT NAME.(EX: CHICAGO O'HARE INTL)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->city,40,94);             //L AN 0040 00095  A1      ASSOCIATED CITY.(EX:  CHICAGO)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->st,2,134);               //L AN 0002 00135  A4      TWO LETTER POST OFFICE CODE FOR THE STATE.
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->state_name,20,136);      //L AN 0020 00137  A4S     STATE NAME.(EX:  ILLINOIS)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->faa_reg,3,156);          //L AN 0003 00157  A6      FAA REGION CODE.(EXAMPLE, ACE = CENTRAL)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->apt_id,4,159);           //L AN 0004 00160  E7      AIRPORT IDENTIFIER.
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->length,5,163);           //R  N 0005 00164  A31     ILS RUNWAY LENGTH IN WHOLE FEET. (EX:  4000)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->width,4,168);            //R  N 0004 00169  A32     ILS RUNWAY WIDTH IN WHOLE FEET. (EX:  100)
      /// ILS SYSTEM INFORMATION
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->cat,9,172);              //L AN 0009 00173  I20     CATEGORY OF THE ILS. (I,II,IIIA)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->own_name,50,181);        //L AN 0050 00182  I10     NAME OF OWNER OF THE FACILITY. (EX: U.S. NAVY)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->fac_oper,50,231);        //L AN 0050 00232  I12     NAME OF THE ILS FACILITY OPERATOR.
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->app_bearing_mag,6,281);  //L AN 0006 00282  I23     ILS APPROACH BEARING IN DEGREES MAGNETIC.
  set_field((char *)&NASRairportbuffer,(char *)&current_ils1->mag_var,3,287);          //L AN 0003 00288  I24     THE MAGNETIC VARIATION AT THE ILS FACILITY.

}
void airport::process_ils2_record()
{
/// LOCALIZER DATA
  set_field((char *)&NASRairportbuffer,(char *)&ils2->lfsn,11,4);                    //L AN 0011 00005  DLID    AIRPORT SITE NUMBER IDENTIFIER. (EX. 04508.*A)
  set_field((char *)&NASRairportbuffer,(char *)&ils2->rwy_end,3,15);                 //L AN 0003 00016  DLID    ILS RUNWAY END IDENTIFIER. (EX: 18,36L)
  set_field((char *)&NASRairportbuffer,(char *)&ils2->type,10,18);                   //L AN 0010 00019  I22     ILS SYSTEM TYPE (SEE ILS1 RECORD TYPE FOR LIST)
  set_field((char *)&NASRairportbuffer,(char *)&ils2->status,22,28);                 //L AN 0022 00029          OPERATIONAL STATUS OF LOCALIZER (OPERATIONAL IFR,
  set_field((char *)&NASRairportbuffer,(char *)&ils2->eff_date,10,50);               //L AN 0010 00051          EFFECTIVE DATE OF LOCALIZER OPERATIONAL STATUS.
  set_field((char *)&NASRairportbuffer,(char *)&ils2->lat_ant,14,61);                //L AN 0014 00061  I4      LATITUDE OF LOCALIZER ANTENNA.(FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&ils2->lat_ant_seconds,11,74);        //L AN 0011 00075  I4S     LATITUDE OF LOCALIZER ANTENNA.(ALL SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&ils2->lon_ant,14,85);                //L AN 0014 00086  I5      LONGITUDE OF LOCALIZER ANTENNA.(FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&ils2->lon_ant_seconds,11,99);        //L AN 0011 00100  I5S     LONGITUDE OF LOCALIZER ANTENNA.(ALL SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&ils2->lat_lon_code,2,110);           //L AN 0002 00111          CODE INDICATING SOURCE OF LATITUDE/LONGITUDE
  set_field((char *)&NASRairportbuffer,(char *)&ils2->dist_frm_app_end,7,112);       //R  N 0007 00113  I36     DISTANCE OF LOCALIZER ANTENNA
  set_field((char *)&NASRairportbuffer,(char *)&ils2->dist_frm_rnwy_cl,4,119);       //R  N 0004 00120          DISTANCE OF LOCALIZER ANTENNA FROM RUNWAY
  set_field((char *)&NASRairportbuffer,(char *)&ils2->dir_of_ant_frm_rnwy,1,123);    //L AN 0001 00124          DIRECTION OF LOCALIZER ANTENNA FROM RUNWAY
  set_field((char *)&NASRairportbuffer,(char *)&ils2->src_dist_info,2,124);          //L AN 0002 00125          CODE INDICATING SOURCE OF DISTANCE
  set_field((char *)&NASRairportbuffer,(char *)&ils2->elev,7,126);                   //R  N 0007 00127          SITE ELEVATION OF LOCALIZER ANTENNA
  set_field((char *)&NASRairportbuffer,(char *)&ils2->freq_mhz,7,133);               //L AN 0007 00134  I31     LOCALIZER FREQUENCY (MHZ). (EX: 108.10)
  set_field((char *)&NASRairportbuffer,(char *)&ils2->back_crs_status,14,140);       //L AN 0015 00141          LOCALIZER BAcK COURSE STATUS (RESTRICTED,
  set_field((char *)&NASRairportbuffer,(char *)&ils2->course_width,5,155);           //R AN 0005 00156  I28     LOCALIZER COURSE WIDTH.(DEGREES AND HUNDREDTHS)
  set_field((char *)&NASRairportbuffer,(char *)&ils2->width_at_threshold,6,160);     //R AN 0007 00161          LOCALIZER COURSE WIDTH AT THRESHOLD.
  set_field((char *)&NASRairportbuffer,(char *)&ils2->dist_from_stop,7,167);         //R  N 0007 00168  I34     LOCALIZER DISTANCE FROM STOP END OF RWY. (FEET)
  set_field((char *)&NASRairportbuffer,(char *)&ils2->dir_from_stop,1,174);          //L AN 0001 00175          LOCALIZER DIRECTION FROM STOP END OF RWY.
  set_field((char *)&NASRairportbuffer,(char *)&ils2->serv_code,2,175);              //L AN 0002 00176          LOCALIZER SERVICES CODE

}
void airport::process_ils3_record()
{
///GLIDE SLOPE DATA
  set_field((char *)&NASRairportbuffer,(char *)&ils3->lfsn,1,4);                    //L AN 0011 00005  DLID    AIRPORT SITE NUMBER IDENTIFIER. (EX. 04508.*A)
  set_field((char *)&NASRairportbuffer,(char *)&ils3->rwy_end,3,15);	              //L AN 0003 00016  DLID    ILS RUNWAY END IDENTIFIER. (EX: 18,36L)
  set_field((char *)&NASRairportbuffer,(char *)&ils3->type,10,18);	                //L AN 0010 00019  I22     ILS SYSTEM TYPE (SEE ILS1 RECORD TYPE FOR LIST)
  set_field((char *)&NASRairportbuffer,(char *)&ils3->status,22,28);	              //L AN 0022 00029          OPERATIONAL STATUS OF GLIDE SLOPE (OPERATIONAL IFR,
  set_field((char *)&NASRairportbuffer,(char *)&ils3->eff_date,10,50);	            //L AN 0010 00051          EFFECTIVE DATE OF GLIDE SLOPE OPERATIONAL STATUS.
  set_field((char *)&NASRairportbuffer,(char *)&ils3->lat_ant,14,60);	              //L AN 0014 00061  I4      LATITUDE OF GLIDE SLOPE TRANSMITTER ANTENNA.
  set_field((char *)&NASRairportbuffer,(char *)&ils3->lat_ant_seconds,11,74);	      //L AN 0011 00075  I4S     LATITUDE OF GLIDE SLOPE TRANSMITTER ANTENNA.
  set_field((char *)&NASRairportbuffer,(char *)&ils3->lon_ant,14,85);	              //L AN 0014 00086  I5      LONGITUDE OF GLIDE SLOPE TRANSMITTER ANTENNA.
  set_field((char *)&NASRairportbuffer,(char *)&ils3->lon_ant_seconds,11,99);	      //L AN 0011 00100  I5S     LONGITUDE OF GLIDE SLOPE TRANSMITTER ANTENNA.
  set_field((char *)&NASRairportbuffer,(char *)&ils3->lat_lon_code,2,110);	        //L AN 0002 00111          CODE INDICATING SOURCE OF LATITUDE/LONGITUDE
  set_field((char *)&NASRairportbuffer,(char *)&ils3->dist_frm_app_end,7,112);	    //R  N 0007 00113  I36     DISTANCE OF GLIDE SLOPE TRANSMITTER ANTENNA
  set_field((char *)&NASRairportbuffer,(char *)&ils3->dist_frm_rnwy_cl,4,119);	    //R  N 0004 00120          DISTANCE OF GLIDE SLOPE TRANSMITTER ANTENNA
  set_field((char *)&NASRairportbuffer,(char *)&ils3->dir_of_ant_frm_rnwy,1,123);   //L AN 0001 00124          DIRECTION OF GLIDE SLOPE TRANSMITTER ANTENNA
  set_field((char *)&NASRairportbuffer,(char *)&ils3->src_dist_info,2,124);	        //L AN 0002 00125          CODE INDICATING SOURCE OF DISTANCE
  set_field((char *)&NASRairportbuffer,(char *)&ils3->elev,7,126);	                //R  N 0007 00127          SITE ELEVATION OF GLIDE SLOPE TRANSMITTER ANTENNA
  set_field((char *)&NASRairportbuffer,(char *)&ils3->gsclass,15,133);	            //L AN 0015 00134  I43     GLIDE SLOPE CLASS/TYPE.
  set_field((char *)&NASRairportbuffer,(char *)&ils3->angle,5,148);	                //L AN 0005 00149  I26     GLIDE SLOPE ANGLE IN DEGREES
  set_field((char *)&NASRairportbuffer,(char *)&ils3->freq,7,153);	                //L AN 0007 00154  I42     GLIDE SLOPE TRANSMISSION FREQUENCY.
  set_field((char *)&NASRairportbuffer,(char *)&ils3->adj_elev,8,160);	            //R  N 0008 00161  I108    ELEVATION OF RUNWAY AT POINT ADJACENT TO THE
}
void airport::process_ils4_record()
{
///DISTANCE MEASURING EQUIPMENT (DME) DATA
  set_field((char *)&NASRairportbuffer,(char *)&ils4->lfsn,11,4);                 //L AN 0011 00005  DLID    AIRPORT SITE NUMBER IDENTIFIER. (EX. 04508.*A)
  set_field((char *)&NASRairportbuffer,(char *)&ils4->rwy_end,3,15);              //L AN 0003 00016  DLID    ILS RUNWAY END IDENTIFIER. (EX: 18,36L)
  set_field((char *)&NASRairportbuffer,(char *)&ils4->type,10,18);                //L AN 0010 00019  I22     ILS SYSTEM TYPE (SEE ILS1 RECORD TYPE FOR LIST)
  set_field((char *)&NASRairportbuffer,(char *)&ils4->status,22,28);              //L AN 0022 00029          OPERATIONAL STATUS OF DME (OPERATIONAL IFR,
  set_field((char *)&NASRairportbuffer,(char *)&ils4->eff_date,10,50);            //L AN 0010 00051          EFFECTIVE DATE OF DME OPERATIONAL STATUS.
  set_field((char *)&NASRairportbuffer,(char *)&ils4->lat_ant,14,60);             //L AN 0014 00061  I4      LATITUDE OF DME TRANSPONDER ANTENNA.
  set_field((char *)&NASRairportbuffer,(char *)&ils4->lat_ant_seconds,11,74);     //L AN 0011 00075  I4S     LATITUDE OF DME TRANSPONDER ANTENNA.
  set_field((char *)&NASRairportbuffer,(char *)&ils4->lon_ant,14,85);             //L AN 0014 00086  I5      LONGITUDE OF DME TRANSPONDER ANTENNA.
  set_field((char *)&NASRairportbuffer,(char *)&ils4->lon_ant_seconds,11,99);     //L AN 0011 00100  I5S     LONGITUDE OF DME TRANSPONDER ANTENNA.
  set_field((char *)&NASRairportbuffer,(char *)&ils4->lat_lon_code,2,110);        //L AN 0002 00111          CODE INDICATING SOURCE OF LATITUDE/LONGITUDE
  set_field((char *)&NASRairportbuffer,(char *)&ils4->dist_frm_app_end,7,112);    //R  N 0007 00113  I36     DISTANCE OF DME TRANSMITTER ANTENNA
  set_field((char *)&NASRairportbuffer,(char *)&ils4->dist_frm_rnwy_cl,4,119);    //R  N 0004 00120          DISTANCE OF DME TRANSPONDER ANTENNA
  set_field((char *)&NASRairportbuffer,(char *)&ils4->dir_of_ant_frm_rnwy,1,123); //L AN 0001 00124          DIRECTION OF DME TRANSPONDER ANTENNA
  set_field((char *)&NASRairportbuffer,(char *)&ils4->src_dist_info,2,124);       //L AN 0002 00125          CODE INDICATING SOURCE OF DISTANCE
  set_field((char *)&NASRairportbuffer,(char *)&ils4->elev,7,126);                //R  N 0007 00127          SITE ELEVATION OF DME TRANSPONDER ANTENNA
  set_field((char *)&NASRairportbuffer,(char *)&ils4->channel,4,133);             //L AN 0004 00134  I98     CHANNEL ON WHICH DISTANCE DATA IS TRANSMITTED.
  set_field((char *)&NASRairportbuffer,(char *)&ils4->dist_frm_stop,7,137);	     //R  N 0007 00138  I104    DISTANCE OF DME

}
void airport::process_ils5_record()
{
///MARKER BEACON DATA
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->lfsn,11,4);                 //L AN 0011 00005  DLID    AIRPORT SITE NUMBER IDENTIFIER. (EX. 04508.*A)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->rwy_end,3,15);              //L AN 0003 00016  DLID    ILS RUNWAY END IDENTIFIER. (EX: 18,36L)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->type,10,18);                //L AN 0010 00019  I22     ILS SYSTEM TYPE (SEE ILS1 RECORD TYPE FOR LIST)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->marker_type,2,28);          //L AN 0002 00029  N/A     MARKER TYPE (IM - INNER MARKER, MM - MIDDLE
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->status,22,30);              //L AN 0022 00031          OPERATIONAL STATUS OF MARKER BEACON (OPERATIONAL
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->eff_date,10,52);            //L AN 0010 00053          EFFECTIVE DATE OF MARKER BEACON OPERATIONAL STATUS.
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->lat_ant,14,62);             //L AN 0014 00063  I4      LATITUDE OF MARKER BEACON. (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->lat_ant_seconds,11,76);     //L AN 0011 00077  I4S     LATITUDE OF MARKER BEACON. (ALL SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->lon_ant,14,87);             //L AN 0014 00088  I5      LONGITUDE OF MARKER BEACON. (FORMATTED)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->lon_ant_seconds,11,101);    //L AN 0011 00102  I5S     LONGITUDE OF MARKER BEACON. (ALL SECONDS)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->lat_lon_code,2,112);        //L AN 0002 00113          CODE INDICATING SOURCE OF LATITUDE/LONGITUDE
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->dist_frm_app_end,7,114);    //R  N 0007 00115  I36     DISTANCE OF MARKER BEACON
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->dist_frm_rnwy_cl,4,121);    //R  N 0004 00122          DISTANCE OF MARKER BEACON
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->dir_of_ant_frm_rnwy,1,125); //L AN 0001 00126          DIRECTION OF MARKER BEACON
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->src_dist_info,2,126);       //L AN 0002 00127          CODE INDICATING SOURCE OF DISTANCE
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->elev,7,128);                //R  N 0007 00129          SITE ELEVATION OF MARKER BEACON
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->fac_type,15,135);           //L AN 0015 00136  I70     FACILITY/TYPE OF MARKER/LOCATOR.
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->loc_id,2,150);              //L AN 0002 00151  I67     LOCATION IDENTIFIER OF BEACON AT MARKER.
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->name,30,152);               //L AN 0030 00153  I81     NAME OF THE MARKER LOCATOR BEACON.
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->freq,3,182);                //R  N 0003 00183  I68     FREQUENCY OF LOCATOR BEACON AT MIDDLE MARKER
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->navaid_type,25,185);        //L AN 0025 00186          LOCATION IDENTIFIER*NAVAID TYPE OF NAVIGATION
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->low_ndb_status,22,210);     //L AN 0022 00211          LOW POWERED NDB STATUS OF MARKER BEACON
  set_field((char *)&NASRairportbuffer,(char *)&current_ils5->serv_provided,30,232);      //L AN 0030 00233          SERVICE PROVIDED BY MARKER.
}
void airport::process_ils6_record()
{
  set_field((char *)&NASRairportbuffer,(char *)&current_ils6->lfsn,11,4);      //L AN 0011 00005  DLID    AIRPORT SITE NUMBER IDENTIFIER
  set_field((char *)&NASRairportbuffer,(char *)&current_ils6->rwy_end,3,15);   //L AN 0003 00016  DLID    ILS RUNWAY END IDENTIFIER.
  set_field((char *)&NASRairportbuffer,(char *)&current_ils6->type,10,18);     //L AN 0010 00019  I22     ILS SYSTEM TYPE (SEE ILS1 RECORD FOR DESCRIPTION)
  set_field((char *)&NASRairportbuffer,(char *)&current_ils6->remarks,350,28); //L AN 0350 00029  RMRKS   ILS REMARKS, FREE-FORM TEXT.
}

void airport::read_NASR_nav_data(char * filename)
{
  printf("read_NASR_nav_data(%s)\n",filename);
  char rtype[5];
  FILE * fp_nav;
  fp_nav  = fopen( filename, "r" );
  if (fp_nav==NULL) {
    printf("!unable to open NASR nav file[%s]\n",filename);
    exit(1);
  }
  printf("Reading %s\n",filename);
  bool done =false;
  while (!done) {
    read_field(fp_nav,(char *)&NASRairportbuffer,sizeof(NASRairportbuffer),tc2);
    set_field((char *)&NASRairportbuffer,(char *)&rtype,4,0);
    if (strncmp(rtype,"NAV1",4)==0) {
      current_nav1 = new(nav1_record);
      if (head_nav1 == NULL) head_nav1 = current_nav1; else last_nav1->next_nav1 = current_nav1;
      current_nav1->nav2_list = NULL;
      current_nav1->nav3_list = NULL;
      current_nav1->nav4_list = NULL;
      current_nav1->nav5_list = NULL;
      current_nav1->nav6_list = NULL;
      process_nav1_record();
      last_nav1 = current_nav1;
    }
    else {
     if (strncmp(rtype,"NAV2",4)==0) {
        current_nav2 = new(nav2_record);
        if (head_nav2 == NULL) head_nav2 = current_nav2; else last_nav2->next_nav2 = current_nav2;
        process_nav2_record();
        last_nav2 = current_nav2;
      }
      else {
        if (strncmp(rtype,"NAV3",4)==0) {
          current_nav3 = new(nav3_record);
          if (head_nav3 == NULL) head_nav3 = current_nav3; else last_nav3->next_nav3 = current_nav3;
          process_nav3_record();
          last_nav3 = current_nav3;
        }
        else {
          if (strncmp(rtype,"NAV4",4)==0) {
            current_nav4 = new(nav4_record);
            if (head_nav4 == NULL) head_nav4 = current_nav4; else last_nav4->next_nav4 = current_nav4;
            process_nav4_record();
            last_nav4 = current_nav4;
          }
          else {
            if (strncmp(rtype,"NAV5",4)==0) {
              current_nav5 = new(nav5_record);
              if (head_nav5 == NULL) head_nav5 = current_nav5; else last_nav5->next_nav5 = current_nav5;
              process_nav5_record();
              last_nav5 = current_nav5;
            }
            else {
             if (strncmp(rtype,"NAV6",4)==0) {
                current_nav6 = new(nav6_record);
                if (head_nav6 == NULL) head_nav6 = current_nav6; else last_nav6->next_nav6 = current_nav6;
                process_nav6_record();
                last_nav6 = current_nav6;
              }
              else {
                printf("ERROR! unknown NAV record type in database\n");
                exit(1);
              }
            }
          }
        }
      }
    }
    if (!nextok(fp_nav)) done=true;
  }
  fclose(fp_nav);
  printf("done\n");
}

void airport::read_nav_data()
{
  char rtype[5];
  FILE * fp_nav;
  std::string fn_nav =paths->OpenEaglePath.c_str();
  fn_nav += "/Update/NASR/";
  fn_nav += "NAV.txt";
  fp_nav  = fopen( fn_nav.c_str(), "r" );
  if (fp_nav==NULL) {
    printf("!unable to open NAV.txt[%s] file\n",fn_nav.c_str());
    exit(1);
  }
  printf("Reading %s\n",fn_nav.c_str());
  bool done =false;
  while (!done) {
    read_field(fp_nav,(char *)&NASRairportbuffer,sizeof(NASRairportbuffer),tc2);
    set_field((char *)&NASRairportbuffer,(char *)&rtype,4,0);
    if (strncmp(rtype,"NAV1",4)==0) {
      current_nav1 = new(nav1_record);
      if (head_nav1 == NULL) head_nav1 = current_nav1; else last_nav1->next_nav1 = current_nav1;
      current_nav1->nav2_list = NULL;
      current_nav1->nav3_list = NULL;
      current_nav1->nav4_list = NULL;
      current_nav1->nav5_list = NULL;
      current_nav1->nav6_list = NULL;
      process_nav1_record();
      last_nav1 = current_nav1;
    }
    else {
     if (strncmp(rtype,"NAV2",4)==0) {
        current_nav2 = new(nav2_record);
        if (head_nav2 == NULL) head_nav2 = current_nav2; else last_nav2->next_nav2 = current_nav2;
        process_nav2_record();
        last_nav2 = current_nav2;
      }
      else {
        if (strncmp(rtype,"NAV3",4)==0) {
          current_nav3 = new(nav3_record);
          if (head_nav3 == NULL) head_nav3 = current_nav3; else last_nav3->next_nav3 = current_nav3;
          process_nav3_record();
          last_nav3 = current_nav3;
        }
        else {
          if (strncmp(rtype,"NAV4",4)==0) {
            current_nav4 = new(nav4_record);
            if (head_nav4 == NULL) head_nav4 = current_nav4; else last_nav4->next_nav4 = current_nav4;
            process_nav4_record();
            last_nav4 = current_nav4;
          }
          else {
            if (strncmp(rtype,"NAV5",4)==0) {
              current_nav5 = new(nav5_record);
              if (head_nav5 == NULL) head_nav5 = current_nav5; else last_nav5->next_nav5 = current_nav5;
              process_nav5_record();
              last_nav5 = current_nav5;
            }
            else {
             if (strncmp(rtype,"NAV6",4)==0) {
                current_nav6 = new(nav6_record);
                if (head_nav6 == NULL) head_nav6 = current_nav6; else last_nav6->next_nav6 = current_nav6;
                process_nav6_record();
                last_nav6 = current_nav6;
              }
              else {
                printf("ERROR! unknown NAV record type in database\n");
                exit(1);
              }
            }
          }
        }
      }
    }
    if (!nextok(fp_nav)) done=true;
  }
  fclose(fp_nav);
}

void airport::read_NASR_fix_data(char * filename)
{
  printf("read_NASR_fix_data(%s)\n",filename);
  char rtype[5];
  FILE * fp_fix;
  fp_fix  = fopen( filename, "r" );
  if (fp_fix==NULL) {
    printf("!unable to open NASR fix file[%s]\n",filename);
    exit(1);
  }
  bool done =false;
  while (!done) {
    read_field(fp_fix,(char *)&NASRairportbuffer,sizeof(NASRairportbuffer),tc2);
    set_field((char *)&NASRairportbuffer,(char *)&rtype,4,0);
    if (strncmp(rtype,"FIX1",4)==0) {
      current_fix1 = new(fix1_record);
      if (head_fix1 == NULL) head_fix1 = current_fix1; else last_fix1->next_fix1 = current_fix1;
      current_fix1->fix2_list = NULL;
      current_fix1->fix3_list = NULL;
      current_fix1->fix4_list = NULL;
      current_fix1->fix5_list = NULL;
      process_fix1_record();
      last_fix1 = current_fix1;
    }
    else {
     if (strncmp(rtype,"FIX2",4)==0) {
        current_fix2 = new(fix2_record);
        if (head_fix2 == NULL) head_fix2 = current_fix2; else last_fix2->next_fix2 = current_fix2;
        process_fix2_record();
        last_fix2 = current_fix2;
      }
      else {
        if (strncmp(rtype,"FIX3",4)==0) {
          current_fix3 = new(fix3_record);
          if (head_fix3 == NULL) head_fix3 = current_fix3; else last_fix3->next_fix3 = current_fix3;
          process_fix3_record();
          last_fix3 = current_fix3;
        }
        else {
          if (strncmp(rtype,"FIX4",4)==0) {
            current_fix4 = new(fix4_record);
            if (head_fix4 == NULL) head_fix4 = current_fix4; else last_fix4->next_fix4 = current_fix4;
            process_fix4_record();
            last_fix4 = current_fix4;
          }
          else {
            if (strncmp(rtype,"FIX5",4)==0) {
              current_fix5 = new(fix5_record);
              if (head_fix5 == NULL) head_fix5 = current_fix5; else last_fix5->next_fix5 = current_fix5;
              process_fix5_record();
              last_fix5 = current_fix5;
            }
            else {
              printf("ERROR! unknown FIX record type in database\n");
              exit(1);
            }
          }
        }
      }
    }
    if (!nextok(fp_fix)) done=true;
  }
  fclose(fp_fix);
  printf("done\n");
}
void airport::read_fix_data()
{
 char rtype[5];
  FILE * fp_fix;
  std::string fn_fix =paths->OpenEaglePath.c_str();
  fn_fix += "/Update/NASR/";
  fn_fix += "FIX.txt";
  fp_fix  = fopen( fn_fix.c_str(), "r" );
  if (fp_fix==NULL) {
    printf("!unable to open FIX.txt [%s] file\n",fn_fix.c_str());
    exit(1);
  }
  printf("Reading %s \n",fn_fix.c_str());
  bool done =false;
  while (!done) {
    read_field(fp_fix,(char *)&NASRairportbuffer,sizeof(NASRairportbuffer),tc2);
    set_field((char *)&NASRairportbuffer,(char *)&rtype,4,0);
    if (strncmp(rtype,"FIX1",4)==0) {
      current_fix1 = new(fix1_record);
      if (head_fix1 == NULL) head_fix1 = current_fix1; else last_fix1->next_fix1 = current_fix1;
      current_fix1->fix2_list = NULL;
      current_fix1->fix3_list = NULL;
      current_fix1->fix4_list = NULL;
      current_fix1->fix5_list = NULL;
      process_fix1_record();
      last_fix1 = current_fix1;
    }
    else {
     if (strncmp(rtype,"FIX2",4)==0) {
        current_fix2 = new(fix2_record);
        if (head_fix2 == NULL) head_fix2 = current_fix2; else last_fix2->next_fix2 = current_fix2;
        process_fix2_record();
        last_fix2 = current_fix2;
      }
      else {
        if (strncmp(rtype,"FIX3",4)==0) {
          current_fix3 = new(fix3_record);
          if (head_fix3 == NULL) head_fix3 = current_fix3; else last_fix3->next_fix3 = current_fix3;
          process_fix3_record();
          last_fix3 = current_fix3;
        }
        else {
          if (strncmp(rtype,"FIX4",4)==0) {
            current_fix4 = new(fix4_record);
            if (head_fix4 == NULL) head_fix4 = current_fix4; else last_fix4->next_fix4 = current_fix4;
            process_fix4_record();
            last_fix4 = current_fix4;
          }
          else {
            if (strncmp(rtype,"FIX5",4)==0) {
              current_fix5 = new(fix5_record);
              if (head_fix5 == NULL) head_fix5 = current_fix5; else last_fix5->next_fix5 = current_fix5;
              process_fix5_record();
              last_fix5 = current_fix5;
            }
            else {
              printf("ERROR! unknown FIX record type in database\n");
              exit(1);
            }
          }
        }
      }
    }
    if (!nextok(fp_fix)) done=true;
  }
  fclose(fp_fix);
}

void airport::read_tower_data()
{
  char rtype[5];
  FILE * fp_tower;
  std::string fn_tower =paths->OpenEaglePath.c_str();
  fn_tower += "/Update/NASR/";
  fn_tower +=  "TWR.txt";
  fp_tower  = fopen( fn_tower.c_str(), "r" );
  if (fp_tower==NULL) {
    printf("!unable to open TWR.txt [%s] file\n",fn_tower.c_str());
    exit(1);
  }
  printf("Reading %s\n",fn_tower.c_str());
  bool done =false;
  int twr1_i = 0;
  while (!done) {
    twr1_i++;
    read_field(fp_tower,(char *)&NASRairportbuffer,sizeof(NASRairportbuffer),tc2);
    set_field((char *)&NASRairportbuffer,(char *)&rtype,4,0);
    if (strncmp(rtype,"TWR1",4)==0) {
      current_twr1 = new(twr1_record);
      if (head_twr1 == NULL) head_twr1 = current_twr1; else last_twr1->next_twr1 = current_twr1;
      current_twr1->twr2 = NULL;
      current_twr1->twr3_list = NULL;
      current_twr1->twr4_list = NULL;
      current_twr1->twr5 = NULL;
      current_twr1->twr6_list = NULL;
      current_twr1->twr7_list = NULL;
      current_twr1->twr8 = NULL;
      current_twr1->twr9_list = NULL;
      process_twr1_record();
      bool found_airport = lookup_airport_and_set_current_by_lfsn((char *)&current_twr1->lfsn);
      if (found_airport) {
        //printf("Tower record associated with airport lfsn [%s] with airport id [%s]\n",current_twr1->lfsn,current_apt->location_identifier);
        current_apt->twr1 = current_twr1;
      }
      else {
        printf("failed to find airport referenced by twr1 lfsn record: lfsn [%s] for record %d and facil id [%s] Likely TRACON\n",
               current_twr1->lfsn,twr1_i,current_twr1->term_com_fac_id);
      }
      last_twr1 = current_twr1;
    }
    else {
      if (strncmp(rtype,"TWR2",4)==0) {
        twr2 = new(twr2_record);
        current_twr1->twr2 = twr2;
        process_twr2_record();
      }
      else {
        if (strncmp(rtype,"TWR3",4)==0) {
          current_twr3 = new(twr3_record);
          if (current_twr1->twr3_list == NULL) current_twr1->twr3_list = current_twr3; else last_twr3->next_twr3 = current_twr3;
          process_twr3_record();
          last_twr3 = current_twr3;
        }
        else {
          if (strncmp(rtype,"TWR4",4)==0) {
            current_twr4 = new(twr4_record);
            if (current_twr1->twr4_list == NULL) current_twr1->twr4_list = current_twr4; else last_twr4->next_twr4 = current_twr4;
            process_twr4_record();
            last_twr4 = current_twr4;
          }
          else {
            if (strncmp(rtype,"TWR5",4)==0) {
              twr5 = new(twr5_record);
              current_twr1->twr5 = twr5;
              process_twr5_record();
            }
            else {
              if (strncmp(rtype,"TWR6",4)==0) {
                current_twr6 = new(twr6_record);
                if (current_twr1->twr6_list == NULL) current_twr1->twr6_list = current_twr6; else last_twr6->next_twr6 = current_twr6;
                process_twr6_record();
                last_twr6 = current_twr6;
              }
              else {
                if (strncmp(rtype,"TWR7",4)==0) {
                  current_twr7 = new(twr7_record);
                  if (current_twr1->twr7_list == NULL) current_twr1->twr7_list = current_twr7; else last_twr7->next_twr7 = current_twr7;
                  process_twr7_record();
                  last_twr7 = current_twr7;
                }
                else {
                  if (strncmp(rtype,"TWR8",4)==0) {
                    twr8 = new(twr8_record);
                    current_twr1->twr8 = twr8;
                    process_twr8_record();
                  }
                  else {
                    if (strncmp(rtype,"TWR9",4)==0) {
                      current_twr9 = new(twr9_record);
                      if (current_twr1->twr9_list == NULL) current_twr1->twr9_list = current_twr9; else last_twr9->next_twr9 = current_twr9;
                      process_twr9_record();
                      last_twr9 = current_twr9;
                    }
                    else {
                      printf("ERROR! unknown Tower record type in database\n");
                      exit(1);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    if (!nextok(fp_tower)) done=true;
  }
  fclose(fp_tower);
}

void airport::read_awos_data()
{
 char rtype[6];
  FILE * fp_awos;
  std::string fn_awos =paths->OpenEaglePath.c_str();
  fn_awos += "/Update/NASR/";
  fn_awos += "AWOS.txt";
  fp_awos  = fopen( fn_awos.c_str(), "r" );
  if (fp_awos==NULL) {
    printf("!unable to open AWOS.txt [%s] file\n",fn_awos.c_str());
    exit(1);
  }
  printf("Reading %s\n",fn_awos.c_str());
  bool done =false;
  int awos1_i = 0;
  while (!done) {
    awos1_i++;
    read_field(fp_awos,(char *)&NASRairportbuffer,sizeof(NASRairportbuffer),tc2);
    set_field((char *)&NASRairportbuffer,(char *)&rtype,5,0);
    if (strncmp(rtype,"AWOS1",5)==0) {
      current_awos1 = new(awos1_record);
      if (head_awos1 == NULL) head_awos1 = current_awos1; else last_awos1->next_awos1 = current_awos1;
      current_awos1->next_awos1 = NULL;
      current_awos1->awos2_list = NULL;
      process_awos1_record();
      bool found_airport = lookup_airport_and_set_current_by_lfsn((char *)&current_awos1->lfsn);
      if (found_airport) {
      //  printf("Tower record is associated with airport lfsn [%s] with airport id [%s]\n",current_twr1->lfsn,current_apt->location_identifier);
        current_apt->awos1 = current_awos1;
      }
      else {
        printf("failed to find airport referenced by awos1 lfsn record: lfsn [%s] for record %d and facil Likely TRACON?\n",
               current_awos1->lfsn,awos1_i);
      }
      last_awos1 = current_awos1;
    }
    else {
      if (strncmp(rtype,"AWOS2",5)==0) {
        current_awos2 = new(awos2_record);
        current_awos2->next_awos2 = NULL;
        if (current_awos1->awos2_list == NULL) current_awos1->awos2_list = current_awos2; else last_awos2->next_awos2 = current_awos2;
        process_awos2_record();
        last_awos2 = current_awos2;
      }
      else {
        printf("ERROR! unknown AWOS record type in database\n");
        exit(1);
      }
    }
    if (!nextok(fp_awos)) done=true;
  }
  fclose(fp_awos);
}


void airport::read_ils_data()
{
  char rtype[5];
  FILE * fp_ils;
  std::string fn_ils =paths->OpenEaglePath.c_str();
  fn_ils += "/Update/NASR/";
  fn_ils += "ILS.txt";
  fp_ils  = fopen( fn_ils.c_str(), "r" );
  if (fp_ils==NULL) {
    printf("!unable to open ILS.txt [%s] file\n",fn_ils.c_str());
    exit(1);
  }
  printf("Reading %s\n",fn_ils.c_str());
  bool done =false;
  int ils1_i = 0;
  while (!done) {
    ils1_i++;
    read_field(fp_ils,(char *)&NASRairportbuffer,sizeof(NASRairportbuffer),tc2);
    set_field((char *)&NASRairportbuffer,(char *)&rtype,5,0);
    if (strncmp(rtype,"ILS1",4)==0) {
      current_ils1 = new(ils1_record);
      if (head_ils1 == NULL) head_ils1 = current_ils1; else last_ils1->next_ils1 = current_ils1;
      current_ils1->next_ils1 = NULL;
      current_ils1->ils2 = NULL;
      current_ils1->ils3 = NULL;
      current_ils1->ils4 = NULL;
      current_ils1->ils5_list = NULL;
      current_ils1->ils6_list = NULL;
      process_ils1_record();
      bool found_airport = lookup_airport_and_set_current_by_lfsn((char *)&current_ils1->lfsn);
      if (found_airport) {
        //printf("Tower record associated with airport lfsn [%s] with airport id [%s]\n",current_twr1->lfsn,current_apt->location_identifier);
        struct airport_ils_record * airport_ils = new(airport_ils_record);
        airport_ils->apt_ils1 = current_ils1;
        if (current_apt->ils_list == NULL) {
          current_apt->ils_list = airport_ils;
          airport_ils->next_apt_ils = NULL;
        }
        else { /// note lifo ordering of list
          airport_ils->next_apt_ils = current_apt->ils_list;
          current_apt->ils_list = airport_ils;
        }
      }
      else {
        printf("failed to find airport referenced by ils1 lfsn record: lfsn [%s] for record %d and facility Likely TRACON?\n",
               current_ils1->lfsn,ils1_i);
      }
      last_ils1 = current_ils1;
    }
    else {
      if (strncmp(rtype,"ILS2",4)==0) {
        ils2 = new(ils2_record);
        if (current_ils1->ils2 == NULL) current_ils1->ils2 = ils2;
        process_ils2_record();
      }
      else {
        if (strncmp(rtype,"ILS3",4)==0) {
          ils3 = new(ils3_record);
          if (current_ils1->ils3 == NULL) current_ils1->ils3 = ils3;
          process_ils3_record();
        }
        else {
          if (strncmp(rtype,"ILS4",4)==0) {
            ils4 = new(ils4_record);
            if (current_ils1->ils4 == NULL) current_ils1->ils4 = ils4;
            process_ils4_record();
          }
          else {
            if (strncmp(rtype,"ILS5",4)==0) {
              current_ils5 = new(ils5_record);
              current_ils5->next_ils5 = NULL;
              if (current_ils1->ils5_list == NULL) current_ils1->ils5_list = current_ils5; else last_ils5->next_ils5 = current_ils5;
              process_ils5_record();
              last_ils5 = current_ils5;
            }
            else {
              if (strncmp(rtype,"ILS6",4)==0) {
                current_ils6 = new(ils6_record);
                current_ils6->next_ils6 = NULL;
                if (current_ils1->ils6_list == NULL) current_ils1->ils6_list = current_ils6; else last_ils6->next_ils6 = current_ils6;
                process_ils6_record();
                last_ils6 = current_ils6;
              }
              else {
                printf("unkown ILS record type[%s]\n",rtype);
                exit(1);
              }
            }
          }
        }
      }
    }
    if (!nextok(fp_ils)) done=true;
  }
  fclose(fp_ils);
}

void airport::read_NASR_apt_dat(char * filename)
{
  char rtype[4];
  FILE * fp_airport;
  fp_airport = fopen( filename, "r" );
  if (fp_airport==NULL) {
    printf("!unable to open APT.txt [%s] file\n",filename);
    exit(1);
  }
  head_apt = new(airport_record); //empty first node
  head_apt->next_apt=NULL;
  head_apt->rwy_list =NULL;
  head_apt->twr1 = NULL;
  head_apt->awos1 = NULL;
 // head_apt->ils1 = NULL;
  last_apt = head_apt;
  printf("Reading %s\n",filename);
  bool done =false;
  int airport_i = 0;
  while (!done) {
    read_field(fp_airport,(char *)&NASRairportbuffer,sizeof(NASRairportbuffer),tc2);
    set_field((char *)&NASRairportbuffer,(char *)&rtype,3,0);
    if (strncmp(rtype,"APT",3)==0) {
      n_apt++;
      current_apt = new(airport_record);
      current_apt->next_apt=NULL;
      current_apt->att_list = NULL;  last_att = NULL;
      current_apt->ars_list = NULL;  last_ars = NULL;
      current_apt->rmk_list = NULL;  last_rmk = NULL;
      current_apt->rwy_list = NULL;  last_rwy = NULL;
      current_apt->twr1 = NULL;
      current_apt->awos1 = NULL;
      current_apt->ils_list = NULL;
      last_apt->next_apt = current_apt;
      last_apt = current_apt;
      airport_i++;
      printf("airport_i %d ",airport_i);
      process_airport_record();
      if (current_apt->landing_facility_type == Airport) n_airport_type++;
      if (n_apt == 1) INFORMATION_EFFECTIVE_DATE = current_apt->information_effective_date;
      struct avl_tree_node *avl_ptr;
      avl_ptr = search_avl_tree ((char *)&current_apt->landing_facility_site_number, false, head_avl_apt_lfsn);
      if (avl_ptr==NULL) {
        avl_ptr = search_avl_tree ((char *)&current_apt->landing_facility_site_number, true, head_avl_apt_lfsn);
        avl_ptr->data_ptr = (void *) current_apt;
      }
      else {
        printf("ERROR! double lfsn code\n");
        exit(1);
      }
      avl_ptr = search_avl_tree ((char *)&current_apt->location_identifier, false, head_avl_apt);
      if (avl_ptr==NULL) {
        avl_ptr = search_avl_tree ((char *)&current_apt->location_identifier, true, head_avl_apt);
        avl_ptr->data_ptr = (void *) current_apt;
      }
    }
    else {
      if (strncmp(rtype,"ATT",3)==0) {
        current_att = new(airport_att_record);
        current_att->next_apt_att = NULL;
        if (current_apt->att_list == NULL) current_apt->att_list = current_att; else last_att->next_apt_att = current_att;
        process_attendance_record();
        last_att = current_att;
      }
      else {
        if (strncmp(rtype,"ARS",3)==0) {
          current_ars = new(airport_ars_record);
          current_ars->next_apt_ars = NULL;
          if (current_apt->ars_list == NULL) current_apt->ars_list = current_ars; else last_ars->next_apt_ars = current_ars;
          process_arrest_record();
          last_ars = current_ars;
        }
        else {
          if (strncmp(rtype,"RWY",3)==0) {
            n_rwy++;
            current_rwy = new(runway_record);
            current_rwy->next_rwy=NULL;
            current_rwy->b_ils1 = current_rwy->r_ils1 = NULL;
            if (current_apt->rwy_list == NULL) current_apt->rwy_list = current_rwy; else  last_rwy->next_rwy = current_rwy;
            process_runway_record();
            last_rwy = current_rwy;
          }
          else {
            if (strncmp(rtype,"RMK",3)==0) {
              current_rmk = new(airport_rmk_record);
              current_rmk->next_apt_rmk = NULL;
              if (current_apt->rmk_list == NULL) current_apt->rmk_list = current_rmk; else last_rmk->next_apt_rmk = current_rmk;
              process_remark_record();
              last_rmk = current_rmk;
            }
          }
        }
      }
    }
    if (!nextok(fp_airport)) done=true;
  }
  printf("n_apt %d\n",n_apt);
  printf("n_rwy %d\n",n_rwy);
  printf("finished reading data\n");
  fclose(fp_airport);
}

void airport::read_airport_data()
{
  char rtype[4];
  FILE * fp_airport;
  FILE * fp_airport_summary;
  std::string airport_summary_fn = paths->OpenEaglePath.c_str();
  airport_summary_fn += "/Update/Summaries/read_airport_data_summary.txt";
  fp_airport_summary = fopen(airport_summary_fn.c_str(),"w++");
  if (fp_airport_summary == NULL) {
    printf("failure to open summary file for read_airport_data()");
  }

 // std::string path = paths->OpenEaglePath.c_str();
  std::string fn_airport =paths->OpenEaglePath.c_str();
  fn_airport += "/Update/NASR/";
  fn_airport += "APT.txt";
  fp_airport = fopen( fn_airport.c_str(), "r" );
  if (fp_airport==NULL) {
    printf("!unable to open APT.txt [%s] file\n",fn_airport.c_str());
    exit(1);
  }
  head_apt = new(airport_record); //empty first node
  head_apt->next_apt=NULL;
  head_apt->rwy_list =NULL;
  head_apt->twr1 = NULL;
  head_apt->awos1 = NULL;
 // head_apt->ils1 = NULL;
  last_apt = head_apt;
  fprintf(fp_airport_summary,"Reading %s\n",fn_airport.c_str());
  bool done =false;
  int airport_i = 0;
  while (!done) {
    read_field(fp_airport,(char *)&NASRairportbuffer,sizeof(NASRairportbuffer),tc2);
    set_field((char *)&NASRairportbuffer,(char *)&rtype,3,0);
    if (strncmp(rtype,"APT",3)==0) {
      n_apt++;
      current_apt = new(airport_record);
      current_apt->next_apt=NULL;
      current_apt->att_list = NULL;  last_att = NULL;
      current_apt->ars_list = NULL;  last_ars = NULL;
      current_apt->rmk_list = NULL;  last_rmk = NULL;
      current_apt->rwy_list = NULL;  last_rwy = NULL;
      current_apt->twr1 = NULL;
      current_apt->awos1 = NULL;
      current_apt->ils_list = NULL;
      last_apt->next_apt = current_apt;
      last_apt = current_apt;
      airport_i++;
      process_airport_record();
      if (current_apt->landing_facility_type == Airport) n_airport_type++;
      if (n_apt == 1) INFORMATION_EFFECTIVE_DATE = current_apt->information_effective_date;
      struct avl_tree_node *avl_ptr;
      avl_ptr = search_avl_tree ((char *)&current_apt->landing_facility_site_number, false, head_avl_apt_lfsn);
      if (avl_ptr==NULL) {
        avl_ptr = search_avl_tree ((char *)&current_apt->landing_facility_site_number, true, head_avl_apt_lfsn);
        avl_ptr->data_ptr = (void *) current_apt;
      }
      else {
        printf("ERROR! double lfsn code\n");
        exit(1);
      }
      avl_ptr = search_avl_tree ((char *)&current_apt->location_identifier, false, head_avl_apt);
      if (avl_ptr==NULL) {
        avl_ptr = search_avl_tree ((char *)&current_apt->location_identifier, true, head_avl_apt);
        avl_ptr->data_ptr = (void *) current_apt;
      }
      else {
        fprintf(fp_airport_summary,"ERROR! double airport with same location_identifier [%s]\n",current_apt->location_identifier);
       // exit(1);
      }
     }
    else {
      if (strncmp(rtype,"ATT",3)==0) {
        current_att = new(airport_att_record);
        current_att->next_apt_att = NULL;
        if (current_apt->att_list == NULL) current_apt->att_list = current_att; else last_att->next_apt_att = current_att;
        process_attendance_record();
        last_att = current_att;
      }
      else {
        if (strncmp(rtype,"ARS",3)==0) {
          current_ars = new(airport_ars_record);
          current_ars->next_apt_ars = NULL;
          if (current_apt->ars_list == NULL) current_apt->ars_list = current_ars; else last_ars->next_apt_ars = current_ars;
          process_arrest_record();
          last_ars = current_ars;
        }
        else {
          if (strncmp(rtype,"RWY",3)==0) {
            n_rwy++;
            current_rwy = new(runway_record);
            current_rwy->next_rwy=NULL;
            current_rwy->b_ils1 = current_rwy->r_ils1 = NULL;
            if (current_apt->rwy_list == NULL) current_apt->rwy_list = current_rwy; else  last_rwy->next_rwy = current_rwy;
            process_runway_record();
            last_rwy = current_rwy;
          }
          else {
            if (strncmp(rtype,"RMK",3)==0) {
              current_rmk = new(airport_rmk_record);
              current_rmk->next_apt_rmk = NULL;
              if (current_apt->rmk_list == NULL) current_apt->rmk_list = current_rmk; else last_rmk->next_apt_rmk = current_rmk;
              process_remark_record();
              last_rmk = current_rmk;
            }
            else {
              fprintf(fp_airport_summary,"ERROR! unknown record type in database\n");
              //exit(1);
            }
          }
        }
      }
    }
    if (!nextok(fp_airport)) done=true;
  }
  fprintf(fp_airport_summary,"n_apt %d\n",n_apt);
  fprintf(fp_airport_summary,"n_rwy %d\n",n_rwy);
  fprintf(fp_airport_summary,"finished reading data\n");
  if (fp_airport != NULL) {
    fclose(fp_airport);
    fp_airport = NULL;
  }
  if (fp_airport_summary != NULL ) {
    fclose(fp_airport_summary);
    fp_airport_summary = NULL;
  }
}

void airport::generate_airport_sign()
{
  printf("generate_airport_sign()::\n");
  tile T;
  double latitude = NASR_coord_to_d(current_apt->airport_latitude_seconds);
  double longitude = NASR_coord_to_d(current_apt->airport_longitude_seconds);
  /// (1) identify tile and path from latitude/longitude
  /// (2) make path to tile permissive
  /// (3) write .ac file to /Scenery/Airports  Note, FlightGear has a /Scenery/Airport directory
  /// (4) write .xml file to /Scenery/Airports
  /// (5) at tile path add line to tile's .stg file (append)
  /// Models/Airports/F/L/G/  airport.ac, airport.xml airport.png
/* ************************************************************************************************* */
/*    (1)(2) tile index and path for given latitude/longitude                                        */
/* ************************************************************************************************* */
  T.set_tile(longitude,latitude);
  T.gen_index();
  std::string tile_index_str = T.gen_index_str();
  std::string tile_base_path = T.gen_base_path();
  std::string ac_master  = paths->OpenEaglePath.c_str();
              ac_master +=  paths->OpenEagleAirportACMaster.c_str();
  std::string xml_master = paths->OpenEaglePath.c_str();
  xml_master += paths-> OpenEagleAirportXMLMaster.c_str();


    if (Airport == current_apt->landing_facility_type)      xml_master += "airport.xml";
    if (Balloonport == current_apt->landing_facility_type)  xml_master += "balloonport.xml";
    if (Seaplanebase == current_apt->landing_facility_type) xml_master += "seaplanebase.xml";
    if (Gliderport == current_apt->landing_facility_type)   xml_master += "gliderport.xml";
    if (Heliport == current_apt->landing_facility_type)     xml_master += "heliport.xml";
    if (Ultralight == current_apt->landing_facility_type)   xml_master += "ultralight.xml";

  printf("xml_master [%s]\n",xml_master.c_str());
//  Airport_sign_path = paths->OpenEagleWrite_ModelsAndObjectsPath.c_str();

//  Airport_sign_path += "/Models/Airports/";

  std::string ac_file = Airport_sign_path;
  ac_file += "airport.ac";
  std::string xml_file = Airport_sign_path;
  xml_file += "airport.xml";
  std::string short_xml_file = "Models/Airports";
              short_xml_file += Short_Airport_sign_path;
  short_xml_file += "/airport.xml";

  std::string png_file = Airport_sign_path;
  png_file += "airport.png";

  std::string stg_path = paths->OpenEagleWrite_ModelsAndObjectsPath.c_str();
  stg_path += "/Objects/";
  stg_path += tile_base_path.c_str();
//  if (!terminal_io) {

  printf("     Airport_sign_path [%s]\n",Airport_sign_path.c_str());  /// "/home/phil/Desktop/FlightGear-OpenEagle2/Scenery/Models/Airports"
  printf("     tile_index_str [%s]\n", tile_index_str.c_str());
  printf("     tile_base_path [%s]\n",tile_base_path.c_str());
  printf("     ac_master      [%s]\n",ac_master.c_str());
  printf("     ac_file        [%s]\n",ac_file.c_str());
  printf("     xml_master     [%s]\n",xml_master.c_str());
  printf("     xml_file       [%s]\n",xml_file.c_str());
  printf("     short_xml_file [%s]\n",short_xml_file.c_str());
  printf("     png_file       [%s]\n",png_file.c_str());
  printf("     stg_path       [%s]\n",stg_path.c_str());

  //}
/************************************************************************/
/* (3)  NOW to copy the airport.ac from Airspace_Textures/airport.ac    */
/************************************************************************/

  command = "cp ";
  command += ac_master.c_str();
  command += " ";
  command += ac_file.c_str();
  command += "\n";
  printf("%s\n",command.c_str());
  if (terminal_io) {
    bool cp_airport_ac = system_io(&command);
    if (!cp_airport_ac) {
      printf("system command failed to write airport.ac [%s]\n",command.c_str());
      exit(1);
    }
  }
/************************************************************************/
/* (3a)  Now to generate airport.png file  Requires ImageMagick         */
/************************************************************************/
/** model
convert -size 256x64 xc:none -font Helvetica-Bold -stroke black \
-pointsize 64 -gravity West -draw "text 64,0 'FLG'" \
-fill none  \
-draw "rectangle 0,0 256,64"  \
-draw "rectangle 1,1 255,63" \
/home/phil/Desktop/OpenEagle/2023-07-17-scenery-build/Scenery/Models/Airports/AZ/FLG/airport.png
**/
  std::string script = "convert -size 256x64 xc:none -font Helvetica-Bold -stroke black \\\n";
  if (current_apt->location_identifier[3] != ' ') {  /// three char: FLG
    current_apt->location_identifier[3] = '\0';
//    script += "-pointsize 64 -gravity West -draw \"text 64,24 ";
    script += "-pointsize 64 -gravity West -draw \"text 64,0 ";
  }
  else{  /// four char: 88AZ
    script += "-pointsize 64 -gravity West -draw \"text 64,0 ";
  }
  script += "\'";
  script += current_apt->location_identifier;
  script += "\'\" \\\n";
  script += "-fill none \\\n";
  script += " -draw \"rectangle 0,0 256,64\" \\\n";
  script += " -draw \"rectangle 1,1 255,63\" \\\n";
  script += png_file.c_str();
  script += "\n";
  printf("%s\n",script.c_str());
  if (terminal_io) {
    bool script_png_ok = system_io(&script);
    if (!script_png_ok) {
      printf("system command failed to write airport.png [%s]\n",script.c_str());
      exit(1);
    }
  }

/************************************************************************/
/* (4)  NOW to copy the airport.xml from Airspace_Textures/airport.xmp    */
/************************************************************************/

  command = "cp ";
  command += xml_master.c_str();
  command += " ";
  command += xml_file.c_str();
  command += "\n";
  printf("%s\n",command.c_str());
  if (terminal_io) {
    bool cp_airport_ac = system_io(&command);
    if (!cp_airport_ac) {
      printf("system command failed to write airport.ac [%s]\n",command.c_str());
      exit(1);
    }
  }


/************************************************************************/
/* (5)  add line to tile's .stg file                                   */
/************************************************************************/
/************************************************************************/
/*               NOW (1) add line to .stg file                          */
/************************************************************************/
/*  segment record includes path for .stg file                          */
/*    but, it is not the complete path                                  */
/*                                                                      */
/*  In the FlightGear data terrain starts at                            */
/*  Scenery in fgdata there is a sub folder/directory:                  */
/*  Scenery/Objects                                                     */
/*  thus the true relative path to the .stg file(s) is                  */
/*  Scenery/Objects/(path from the segment record)                      */
/*                                                                      */
/*  Thus working with data in a "Current" folder/directory              */
/*  Make an Objects folder and copy the FlighGear Object contents       */
/*  in. We will be appending lines into the .stg files                  */
/*                                                                      */
/*  With the .ac .xml and .stg additions to the Models and Objects      */
/*  copied to the FlightGear root data we're ready add translucent      */
/*  boundaries for the airspace into the scene.                         */
/*                                                                      */
/************************************************************************/

  command = "mkdir -p ";
  command += stg_path.c_str();
  command += "\n";
  printf("stg_path: %s\n",command.c_str());
  if (terminal_io) {
    bool tile_path_ok = system_io(&command);
    if (!tile_path_ok) {
      printf("okay why is system command failing for string [%s]\n",command.c_str());
      exit(1);
    }
  }
  std::string stg_full_filename = stg_path.c_str();
  stg_full_filename += "/";
  stg_full_filename += tile_index_str.c_str();
  stg_full_filename += ".stg";

  char _add_line[200];
  double elevation_meter = std::stod(current_apt->airport_elevation,NULL)*SG_FEET_TO_METER;
  sprintf(_add_line,"OBJECT_SHARED %s %10.5f %10.4f %10.1f 0.00\n",short_xml_file.c_str(),
          NASR_coord_to_d((char *)current_apt->airport_longitude_seconds),
          NASR_coord_to_d((char *)current_apt->airport_latitude_seconds),
          elevation_meter);
  printf("          addline to .stg file: %s\n",stg_full_filename.c_str());
  if (terminal_io) {
    printf("open [%s] and addline [%s]\n",stg_full_filename.c_str(),_add_line);
    FILE * fp = fopen(stg_full_filename.c_str(),"a+");
    if (fp != NULL) {
      fprintf(fp,"%s\n",_add_line);
      fclose(fp);
      fp = NULL;
    }
    else {
      printf("unable to add line to [%s]\n",stg_full_filename.c_str());
      exit(1);
     }
  }
  else {
      printf("FILE * fp = fopen(%s, a+ )\nto _addline: [%s]\n",stg_full_filename.c_str(),_add_line);
  }
}

void airport::generate_airport_files()
{
  printf("generate_airport_files()\n");
  current_apt = head_apt->next_apt;
  int apt_i = 0;
  int apt_n = 0;
  while (current_apt!=NULL) {
    Airport_sign_path = paths->OpenEagleWrite_ModelsAndObjectsPath.c_str();
    Short_Airport_sign_path = "";
/* ************************************************************************************************* */
/*    make Airport_sign_path i.e Models/Airports/ST/FLG path to store information on airport FLG     */
/* ************************************************************************************************* */
    if (Airport == current_apt->landing_facility_type) {

      Short_Airport_sign_path += "/";
      Short_Airport_sign_path += current_apt->st;
      Short_Airport_sign_path += "/";
      Short_Airport_sign_path += current_apt->location_identifier;

      Airport_sign_path += "/Models/Airports/";
      Airport_sign_path += current_apt->st;
      Airport_sign_path += "/";
      Airport_sign_path += current_apt->location_identifier;
      printf("Airport_sign_path [%s]\n",Airport_sign_path.c_str());
      /// Make Airport_Sign_path if needed
      command = "mkdir -p ";
      command += Airport_sign_path;
      printf("%s\n",command.c_str());
      if (terminal_io) {
        bool path_ok = system_io(&command);
        if (!path_ok) {
          printf("system command failed for making Airport_sign_path [%s]\n",command.c_str());
          exit(1);
        }
      }

      Airport_sign_path += "/";
      printf("     location_identifier [%s]",current_apt->location_identifier);
      apt_n ++;
      printf("  sign for %d of %d airports:",apt_n, n_airport_type);
      generate_airport_sign();
    }
//    else printf("     not Airport, skipped");
    current_apt=current_apt->next_apt;
    apt_i++;
  }
}



void airport :: generate_nav_files()
{

  /** current_nav BUG **/
  /**
  printf("generate_nav_files()\n");
  current_nav = head_nav->next_nav;
  int nav_i = 0;
  int nav_n = 0;
  while (current_nav!=NULL) {
    Nav_sign_path = Nav_sign_base_path;
    Short_Nav_sign_path = Short_Nav_sign_base_path;
    **/
/* ************************************************************************************************* */
/*    make Nav_sign_path i.e Models/Nav..???Airports/ST/FLG path to store information on airport FLG     */
/* ************************************************************************************************* */
/**
    if (Airport == current_apt->landing_facility_type) {

      Short_Airport_sign_path += "/";
      Short_Airport_sign_path += current_apt->st;
      Short_Airport_sign_path += "/";
      Short_Airport_sign_path += current_apt->location_identifier;

      Airport_sign_path += "/";
      Airport_sign_path += current_apt->st;
      Airport_sign_path += "/";
      Airport_sign_path += current_apt->location_identifier;

      /// Make Airport_Sign_path if needed
      command = "mkdir -p ";
      command += Airport_sign_path;
      printf("%s\n",command.c_str());
      if (terminal_io) {
        bool path_ok = system_io(&command);
        if (!path_ok) {
          printf("system command failed for making Airport_sign_path [%s]\n",command.c_str());
          exit(1);
        }
      }

      Airport_sign_path += "/";
      printf("     location_identifier [%s]",current_apt->location_identifier);
      apt_n ++;
      printf("  sign for %d of %d airports:",apt_n, n_airport_type);
      generate_airport_sign();
    }
//    else printf("     not Airport, skipped");
    current_apt=current_apt->next_apt;
    apt_i++;
  }
**/
}

void airport::generate_flightgear_apt_dat(char * flightgear_apt_path)
{
  printf("generate_flightgear_apt_dat(%s)\n",flightgear_apt_path);
  std::string old_apt = flightgear_apt_path;
  old_apt += "/apt.dat.gz";
  FILE* test_open_fp = fopen(old_apt.c_str(),"r");
  printf("test to see if old fix exists [%s]\n",old_apt.c_str());
  if (test_open_fp != NULL) {
    fclose(test_open_fp);
    printf("old apt dat file [%s] exists, will backup/retire\n",old_apt.c_str());
    std::string command = "cp ";
    command += old_apt;
    command += " ";
    command += flightgear_apt_path;
    command += "/";
    command += formatted_time_year_month_day();
    command += "-retired-";
    command += "apt.dat.gz";
    system_io(&command);
  }
/// now for the fix.dat file
  std::string apt_dat = flightgear_apt_path;
  apt_dat += "/apt.dat";
  printf("generate_flightgear_apt_dat():: %s\n",apt_dat.c_str());
  FILE * fp = fopen(apt_dat.c_str(),"w++");
  fprintf(fp,"I\n"); // line 1
  fprintf(fp,"1000 NASR effective date: %s",current_apt->information_effective_date);
  fprintf(fp,"  This data is in the public domain as it was generated from FAA NASR database sources\n\n\n"); //2,3,4
  current_apt = head_apt->next_apt;
  while (current_apt!=NULL) {
    if (Airport == current_apt->landing_facility_type) {
      fprintf(fp,"1 %s -1 -1 %s %s\n",current_apt->airport_elevation,current_apt->location_identifier,current_apt->name);
      current_rwy = current_apt->rwy_list;
      while (current_rwy != NULL) {
        if (current_rwy->r_id[0] != '\0') {
          double latitude  = NASR_coord_to_d(current_rwy->b_latitude_seconds);
          double longitude = NASR_coord_to_d(current_rwy->b_longitude_seconds);
          fprintf(fp,"100 %s 1  0 0.25 0 3 1 %s %15.9f %15.9f 0.0 0.0 3 0 0 0 %s %10.5f %10.4f 0.0 0.0 3 8 0 0\n",
                current_rwy->runway_width,
                current_rwy->b_id,
                latitude,
                longitude,
                current_rwy->r_id,
                NASR_coord_to_d(current_rwy->r_latitude_seconds),
                NASR_coord_to_d(current_rwy->r_longitude_seconds)
                );
        }
        current_rwy = current_rwy->next_rwy;
      }
      if (current_apt->airport_official_icao[0] != ' ') {
        fprintf(fp,"1 %s -1 -1 %s %s\n",current_apt->airport_elevation,current_apt->airport_official_icao,current_apt->name);
        current_rwy = current_apt->rwy_list;
        while (current_rwy != NULL) {
          if (current_rwy->r_id[0] != '\0') {
            double latitude  = NASR_coord_to_d(current_rwy->b_latitude_seconds);
            double longitude = NASR_coord_to_d(current_rwy->b_longitude_seconds);
            fprintf(fp,"100 %s 1  0 0.25 0 3 1 %s %15.9f %15.9f 0.0 0.0 3 0 0 0 %s %10.5f %10.4f 0.0 0.0 3 8 0 0\n",
                current_rwy->runway_width,
                current_rwy->b_id,
                latitude,
                longitude,
                current_rwy->r_id,
                NASR_coord_to_d(current_rwy->r_latitude_seconds),
                NASR_coord_to_d(current_rwy->r_longitude_seconds)
                );
          }
          current_rwy = current_rwy->next_rwy;
        }
      }
    }
    fprintf(fp,"\n");
    current_apt=current_apt->next_apt;
  }
  fprintf(fp,"99\n");
  fclose(fp);
  command = "gzip ";
  command += apt_dat;
  bool gzipped_apt_ok = system_io(&command);
  if (!gzipped_apt_ok) {
    printf("system command failed to gzip apt.dat to apt.dat.gz[%s]\n",command.c_str());
    exit(1);
  }
  printf("fini\n");
}

void airport::generate_flightgear_apt_dat()
{
  printf("generate_flightgear_apt_dat()\n");
  FILE * fp_apt_log;
  std::string apt_log  = paths->OpenEaglePath.c_str();
              apt_log += "/Update/Summaries/apt_log.txt";
  fp_apt_log = fopen(apt_log.c_str(),"w++");
  current_apt = head_apt->next_apt;
  int apt_i = 0;
  FILE * fp;
  std::string apt_dat = paths->OpenEagle_FlightGear_Path.c_str();
  apt_dat += "/Airports/";
  apt_dat += "apt.dat";
  fprintf(fp_apt_log,"generate_flightgear_apt_data():: %s\n",apt_dat.c_str());
  fp = fopen(apt_dat.c_str(),"w++");
  fprintf(fp,"I\n"); // line 1
  fprintf(fp,"1000 NASR effective date: %s",current_apt->information_effective_date);
  fprintf(fp,"  This data is in the public domain as it was generated from FAA NASR database sources\n\n\n"); //2,3,4
  while (current_apt!=NULL) {
    if (Airport == current_apt->landing_facility_type) {
      fprintf(fp,"1 %s -1 -1 %s %s\n",current_apt->airport_elevation,current_apt->location_identifier,current_apt->name);
      current_rwy = current_apt->rwy_list;
      while (current_rwy != NULL) {
        if (current_rwy->r_id[0] != '\0') {
          double latitude  = NASR_coord_to_d(current_rwy->b_latitude_seconds);
          double longitude = NASR_coord_to_d(current_rwy->b_longitude_seconds);
          fprintf(fp,"100 %s 1  0 0.25 0 3 1 %s %15.9f %15.9f 0.0 0.0 3 0 0 0 %s %10.5f %10.4f 0.0 0.0 3 8 0 0\n",
                current_rwy->runway_width,
                current_rwy->b_id,
                latitude,
                longitude,
                current_rwy->r_id,
                NASR_coord_to_d(current_rwy->r_latitude_seconds),
                NASR_coord_to_d(current_rwy->r_longitude_seconds)
                );
        }
        current_rwy = current_rwy->next_rwy;
      }
      if (current_apt->airport_official_icao[0] != ' ') {
        fprintf(fp,"1 %s -1 -1 %s %s\n",current_apt->airport_elevation,current_apt->airport_official_icao,current_apt->name);
        current_rwy = current_apt->rwy_list;
        while (current_rwy != NULL) {
          if (current_rwy->r_id[0] != '\0') {
            double latitude  = NASR_coord_to_d(current_rwy->b_latitude_seconds);
            double longitude = NASR_coord_to_d(current_rwy->b_longitude_seconds);
            fprintf(fp,"100 %s 1  0 0.25 0 3 1 %s %15.9f %15.9f 0.0 0.0 3 0 0 0 %s %10.5f %10.4f 0.0 0.0 3 8 0 0\n",
                current_rwy->runway_width,
                current_rwy->b_id,
                latitude,
                longitude,
                current_rwy->r_id,
                NASR_coord_to_d(current_rwy->r_latitude_seconds),
                NASR_coord_to_d(current_rwy->r_longitude_seconds)
                );
          }
          current_rwy = current_rwy->next_rwy;
        }
      }
    }
    fprintf(fp,"\n");
    current_apt=current_apt->next_apt;
    apt_i++;
  }
  fprintf(fp,"99\n");
  fclose(fp);
  fp = NULL;
  command = "gzip ";
  command += paths->OpenEagle_FlightGear_Path.c_str();
  command += "/Airports/apt.dat\n";
  fprintf(fp_apt_log,"%s\n",command.c_str());
  if (fp_apt_log != NULL) {
    fclose(fp_apt_log);
    fp_apt_log = NULL;
  }
  printf("%s\n",command.c_str());
  if (terminal_io) {
    bool gzipped_apt_ok = system_io(&command);
    if (!gzipped_apt_ok) {
      printf("system command failed to gzip apt.dat to apt.dat.gz[%s]\n",command.c_str());
      exit(1);
    }
  }
}
void airport::generate_flightgear_metar_dat()
{
  printf("generate_flightgear_metar_dat()\n");
  FILE * fp_metar_log;
  std::string metar_log  = paths->OpenEaglePath.c_str();
              metar_log += "/Update/Summaries/metar_log.txt";
  fp_metar_log = fopen(metar_log.c_str(),"w++");
  current_apt = head_apt->next_apt;
  int apt_i = 0;
  FILE * fp;
  std::string metar_dat = paths->OpenEagle_FlightGear_Path.c_str();
  metar_dat += "/Airports/";
  metar_dat += "metar.dat";
  fprintf(fp_metar_log,"generate_flightgear_metar_dat():: %s\n",metar_dat.c_str());
  fp = fopen(metar_dat.c_str(),"w++");
  fprintf(fp,"# List of airports known to have metar data available.\n");
  fprintf(fp,"# replacement metar.dat.gz for flightgear; NASR effective date: %s\n",current_apt->information_effective_date);
  fprintf(fp,"# This data is in the public domain and was was generated from FAA NASR database sources\n");
  while (current_apt!=NULL) {
    if (Airport == current_apt->landing_facility_type) {
      if ( current_apt->awos1  != NULL ) {
        if (current_apt->airport_official_icao[0] != ' ') {
          fprintf(fp,"%s\n",current_apt->airport_official_icao);
        }
        else {
          fprintf(fp,"%s\n",current_apt->location_identifier);
        }
      }
    }
    current_apt=current_apt->next_apt;
    apt_i++;
  }
  fclose(fp);
  command ="gzip ";
  command += paths->OpenEagle_FlightGear_Path.c_str();
  command += "/Airports/metar.dat\n";
  fprintf(fp_metar_log,"%s\n",command.c_str());
  fclose(fp_metar_log);
  printf("%s\n",command.c_str());
  if (terminal_io) {
    bool gzipped_metar_ok = system_io(&command);
    if (!gzipped_metar_ok) {
      printf("system command failed to gzip metar.dat to metar.dat.gz[%s]\n",command.c_str());
      exit(1);
    }
  }
}

void airport::generate_flightgear_fix_dat(char * flightgear_fix_path)
{
  printf("generate_flightgear_fix_dat(%s)\n",flightgear_fix_path);
  std::string old_fix = flightgear_fix_path;
  old_fix += "/fix.dat.gz";
  FILE* test_open_fp = fopen(old_fix.c_str(),"r");
  printf("test to see if old fix exists [%s]\n",old_fix.c_str());
  if (test_open_fp != NULL) {
    fclose(test_open_fp);
    printf("old fix dat file [%s] exists, will backup/retire\n",old_fix.c_str());
    std::string command = "cp ";
    command += old_fix;
    command += " ";
    command += flightgear_fix_path;
    command += "/";
    command += formatted_time_year_month_day();
    command += "-retired-";
    command += "fix.dat.gz";
    system_io(&command);
  }
/// now for the fix.dat file
  std::string fix_dat = flightgear_fix_path;
  fix_dat += "/fix.dat";
  printf("generate_flightgear_fix_dat():: %s\n",fix_dat.c_str());
  FILE * fp = fopen(fix_dat.c_str(),"w++");
  fprintf(fp,"I\n"); // line 1
  fprintf(fp,"1000 generated from NASR data on: %s",formatted_time_year_month_day());
  fprintf(fp,"  This data is in the public domain as it was generated from FAA NASR database sources\n\n");
  current_fix1 = head_fix1;
  while (current_fix1 != NULL) {
   // printf("current_fix1 loop\n");
    fprintf(fp," %12.6f ",NASR_f_coord_to_d(current_fix1->lat));
    fprintf(fp," %12.6f ",NASR_f_coord_to_d(current_fix1->lon));
    fprintf(fp," %s\n",current_fix1->NAS_id);
    current_fix1 = current_fix1->next_fix1;
  }
  fprintf(fp,"99\n");
  fclose(fp);
  command = "gzip ";
  command += fix_dat;
  bool gzipped_fix_ok = system_io(&command);
  if (!gzipped_fix_ok) {
    printf("system command failed to gzip fix.dat to fix.dat.gz[%s]\n",command.c_str());
    exit(1);
  }
  printf("fini\n");
}

void airport::generate_flightgear_fix_dat()
{
  printf("generate_flightgear_fix_dat()\n");

  FILE * fp_fix_log;
  std::string fix_log  = paths->OpenEaglePath.c_str();
              fix_log += "/Update/Summaries/fix_log.txt";
  fp_fix_log = fopen(fix_log.c_str(),"w++");
  current_fix1 = head_fix1;
  FILE * fp;
  std::string fix_dat = paths->OpenEagle_FlightGear_Path.c_str();
  fix_dat += "/Navaids/";
  fix_dat += "fix.dat";
  fprintf(fp_fix_log,"generate_flightgear_fix_dat():: %s\n",fix_dat.c_str());
  printf("generate_flightgear_fix_dat():: %s\n",fix_dat.c_str());
  fp = fopen(fix_dat.c_str(),"w++");
  fprintf(fp,"I\n"); // line 1
  fprintf(fp,"1000 NASR effective date: %s",INFORMATION_EFFECTIVE_DATE.c_str());
  fprintf(fp,"  This data is in the public domain as it was generated from FAA NASR database sources\n\n");
  while (current_fix1 != NULL) {
   // printf("current_fix1 loop\n");
    fprintf(fp," %12.6f ",NASR_f_coord_to_d(current_fix1->lat));
    fprintf(fp," %12.6f ",NASR_f_coord_to_d(current_fix1->lon));
    fprintf(fp," %s\n",current_fix1->NAS_id);
    current_fix1 = current_fix1->next_fix1;
  }
  fprintf(fp,"99\n");
  fclose(fp);
  command = "gzip ";
  command += paths->OpenEagle_FlightGear_Path.c_str();
  command += "/Navaids/fix.dat\n";
  fprintf(fp_fix_log,"%s\n",command.c_str());
  fclose(fp_fix_log);
  printf("%s\n",command.c_str());
  if (terminal_io) {
    bool gzipped_fix_ok = system_io(&command);
    if (!gzipped_fix_ok) {
      printf("system command failed to gzip fix.dat to fix.dat.gz[%s]\n",command.c_str());
      exit(1);
    }
  }
}
int airport::prot_alt_freq_to_miles()
{
/// only doing below 18,000 feet
   if (current_nav1->prot_alt_freq[0] == 'T') return 25; else return 40;
}

void airport::generate_flightgear_nav_dat(char * flightgear_nav_path)
{
  printf("generate_flightgear_nav_dat(%s)\n",flightgear_nav_path);
  std::string old_nav = flightgear_nav_path;
  old_nav += "/nav.dat.gz";
  FILE* test_open_fp = fopen(old_nav.c_str(),"r");
  printf("test to see if old nav exists [%s]\n",old_nav.c_str());
  if (test_open_fp != NULL) {
    fclose(test_open_fp);
    printf("old nav dat file [%s] exists, will backup/retire\n",old_nav.c_str());
    std::string command = "cp ";
    command += old_nav;
    command += " ";
    command += flightgear_nav_path;
    command += "/";
    command += formatted_time_year_month_day();
    command += "-retired-";
    command += "nav.dat.gz";
    system_io(&command);
  }
  current_nav1 = head_nav1;
/// now for the fix.dat file
  std::string nav_dat = flightgear_nav_path;
  nav_dat += "/nav.dat";
  printf("generate_flightgear_nav_dat():: %s\n",nav_dat.c_str());
  FILE * fp = fopen(nav_dat.c_str(),"w++");
  fprintf(fp,"I\n"); // line 1
  fprintf(fp,"810 NASR effective date: %s",current_nav1->eff_date); //INFORMATION_EFFECTIVE_DATE.c_str());  /// ruh data is on nav1 record
  fprintf(fp,"  This data is in the public domain as it was generated from FAA NASR database sources\n\n");
  while (current_nav1 != NULL) {
    if (strncmp(current_nav1->fac_type,"NDB",3) == 0) { /// also covers NDB/DME
      std::string elevation = "0";
      if (strncmp(current_nav1->elevation," ",1) != 0) elevation = current_nav1->elevation;
      std::string freq = "0";
      if (strncmp(current_nav1->freq," ",1) != 0) freq = current_nav1->freq;
      fprintf(fp,"2 %15.8f %15.8f %s %s %d 0.0 %s %s %s\n",
              NASR_coord_to_d(current_nav1->lat_seconds),
              NASR_coord_to_d(current_nav1->lon_seconds),
              elevation.c_str(),
              freq.c_str(),
              prot_alt_freq_to_miles(),
              current_nav1->nav_fac_id,
              current_nav1->name,
              current_nav1->fac_type
              );
    }
    if (strncmp(current_nav1->fac_type,"VOR",3) == 0) {  /// also covers VOR/DME
      std::string elevation = "0";
      if (strncmp(current_nav1->elevation," ",1) != 0) elevation = current_nav1->elevation;
      std::string freq = "0";
      if (strncmp(current_nav1->freq," ",1) != 0) freq = current_nav1->freq;
      fprintf(fp,"3 %15.8f %15.8f %s %s %d 0.0 %s %s %s\n",
              NASR_coord_to_d(current_nav1->lat_seconds),
              NASR_coord_to_d(current_nav1->lon_seconds),
              elevation.c_str(),
              freq.c_str(),
              prot_alt_freq_to_miles(),
              current_nav1->nav_fac_id,
              current_nav1->name,
              current_nav1->fac_type
              );
    }
    if (strncmp(current_nav1->fac_type,"DME",3) == 0) {
      std::string elevation = "0";
      if (strncmp(current_nav1->elevation," ",1) != 0) elevation = current_nav1->elevation;
      std::string freq = "0";
      if (strncmp(current_nav1->freq," ",1) != 0) freq = current_nav1->freq;
      fprintf(fp,"13 %15.8f %15.8f %s %s %d 0.0 %s %s %s\n",
              NASR_coord_to_d(current_nav1->lat_seconds),
              NASR_coord_to_d(current_nav1->lon_seconds),
              elevation.c_str(),
              freq.c_str(),
              prot_alt_freq_to_miles(),
              current_nav1->nav_fac_id,
              current_nav1->name,
              current_nav1->fac_type
              );
    }
    current_nav1 = current_nav1->next_nav1;
  }
  fprintf(fp,"99\n");
  fclose(fp);
  command = "gzip ";
  command += nav_dat;
  bool gzipped_nav_ok = system_io(&command);
  if (!gzipped_nav_ok) {
    printf("system command failed to gzip nav.dat to nav.dat.gz[%s]\n",command.c_str());
    exit(1);
  }
  printf("fini\n");
}

void airport::generate_flightgear_nav_dat()
{
  printf("generate_flightgear_nav_dat()\n");
  FILE * fp_nav_log;
  std::string nav_log  = paths->OpenEaglePath.c_str();
              nav_log += "/Update/Summaries/nav_log.txt";
  fp_nav_log = fopen(nav_log.c_str(),"w++");
  current_nav1 = head_nav1;
  FILE * fp;
  std::string nav_dat = paths->OpenEagle_FlightGear_Path.c_str();
  nav_dat += "/Navaids/";
  nav_dat += "nav.dat";
  fprintf(fp_nav_log,"generate_flightgear_nav_dat():: %s\n",nav_dat.c_str());
  fp = fopen(nav_dat.c_str(),"w++");
  fprintf(fp,"I\n"); // line 1
  fprintf(fp,"810 NASR effective date: %s",INFORMATION_EFFECTIVE_DATE.c_str());
  fprintf(fp,"  This data is in the public domain as it was generated from FAA NASR database sources\n\n");
  while (current_nav1 != NULL) {
    if (strncmp(current_nav1->fac_type,"NDB",3) == 0) { /// also covers NDB/DME
      std::string elevation = "0";
      if (strncmp(current_nav1->elevation," ",1) != 0) elevation = current_nav1->elevation;
      std::string freq = "0";
      if (strncmp(current_nav1->freq," ",1) != 0) freq = current_nav1->freq;
      fprintf(fp,"2 %15.8f %15.8f %s %s %d 0.0 %s %s %s\n",
              NASR_coord_to_d(current_nav1->lat_seconds),
              NASR_coord_to_d(current_nav1->lon_seconds),
              elevation.c_str(),
              freq.c_str(),
              prot_alt_freq_to_miles(),
              current_nav1->nav_fac_id,
              current_nav1->name,
              current_nav1->fac_type
              );
    }
    if (strncmp(current_nav1->fac_type,"VOR",3) == 0) {  /// also covers VOR/DME
      std::string elevation = "0";
      if (strncmp(current_nav1->elevation," ",1) != 0) elevation = current_nav1->elevation;
      std::string freq = "0";
      if (strncmp(current_nav1->freq," ",1) != 0) freq = current_nav1->freq;
      fprintf(fp,"3 %15.8f %15.8f %s %s %d 0.0 %s %s %s\n",
              NASR_coord_to_d(current_nav1->lat_seconds),
              NASR_coord_to_d(current_nav1->lon_seconds),
              elevation.c_str(),
              freq.c_str(),
              prot_alt_freq_to_miles(),
              current_nav1->nav_fac_id,
              current_nav1->name,
              current_nav1->fac_type
              );
    }
    if (strncmp(current_nav1->fac_type,"DME",3) == 0) {
      std::string elevation = "0";
      if (strncmp(current_nav1->elevation," ",1) != 0) elevation = current_nav1->elevation;
      std::string freq = "0";
      if (strncmp(current_nav1->freq," ",1) != 0) freq = current_nav1->freq;
      fprintf(fp,"13 %15.8f %15.8f %s %s %d 0.0 %s %s %s\n",
              NASR_coord_to_d(current_nav1->lat_seconds),
              NASR_coord_to_d(current_nav1->lon_seconds),
              elevation.c_str(),
              freq.c_str(),
              prot_alt_freq_to_miles(),
              current_nav1->nav_fac_id,
              current_nav1->name,
              current_nav1->fac_type
              );
    }
    current_nav1 = current_nav1->next_nav1;
  }
  fprintf(fp,"99\n");
  fclose(fp);
  command = "gzip ";
  command += paths->OpenEagle_FlightGear_Path.c_str();
  command += "/Navaids/nav.dat\n";
  fprintf(fp_nav_log,"%s\n",command.c_str());
  fclose(fp_nav_log);
  printf("%s\n",command.c_str());
  if (terminal_io) {
    bool gzipped_nav_ok = system_io(&command);
    if (!gzipped_nav_ok) {
      printf("system command failed to gzip nav.dat to nav.dat.gz[%s]\n",command.c_str());
      exit(1);
    }
  }
}

void airport::free_airport_data()
{
  printf("free_airport_data() entry\n");
  current_apt = head_apt;;
  while (head_apt!=NULL) {
    current_apt=head_apt;
    head_apt = head_apt->next_apt;
    head_ars = current_apt->ars_list;
    while (head_ars != NULL) {
      current_ars = head_ars;
      head_ars = head_ars->next_apt_ars;
      free(current_ars);
    }
    head_att = current_apt->att_list;
    while (head_att != NULL) {
      current_att = head_att;
      head_att = head_att->next_apt_att;
      free(current_ars);
    }
    head_rwy = current_apt->rwy_list;
    while (head_rwy!=NULL) {
      current_rwy=head_rwy;
      head_rwy = head_rwy->next_rwy;
      free(current_rwy);
    }
    head_rmk = current_apt->rmk_list;
    while (head_rmk != NULL) {
      current_rmk = head_rmk;
      head_rmk = head_rmk->next_apt_rmk;
      free(current_rmk);
    }
    free( current_apt);
  }
  printf("head_apt->NULL should be normal shutdown?\n");
}


