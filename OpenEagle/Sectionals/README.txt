Map Making
How to use the scripts

(1) go to:
https://www.faa.gov/air_traffic/flight_info/aeronav/digital_products/vfr/

(2) scripts are designed to work with the 56-day-sets for the:
Sectiona Set (zip) file and
Grand Canyon Set (zip) file

(2a) in the alternative, you can download the Sectional Charts
by name and the Grand Canyon set.  The files for the US lower 48 states
are listed in the US_Lower_48_States_list.txt file.

The 56-day_sets download should be done in the off hours to avoid download failures/restarts.

Once file(s) are downloaded put them in a Sectionals-year-month-day directory showing their
edition date.

Then copy to 56-day-sets directory here or the Grand Canyon and Sectional directories for individual downloads

Processing the 56-day-sets is performed by running the following scripts in order:
unpack_Grand_Canyon-56-day-sets.sh
unpack_Sectional-56-day-sets.sh
distribute_tif_files-56-day-set.sh
generate_maps-56-day-sets.sh

The generate_maps-56-day-sets.sh takes a little over an hour on a
Aorus Gaming Motherboard: X570SI PRO AX, with and AMD AM4 class CPU with 16 cores.

