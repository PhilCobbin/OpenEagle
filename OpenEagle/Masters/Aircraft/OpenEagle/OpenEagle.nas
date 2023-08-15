
####################################################################################################
#     //////////////////////////////////////////////////////////////////////////////////////////////
#     /////                           filename:  OpenEagle.nas                                //////
#     //////////////////////////////////////////////////////////////////////////////////////////////
#     //////                                  September 14, 2016 clean up                     //////
#     //////                                                                                  //////
#     //////                            OpenEagle.nas                                         //////
#     //////                     Open Eagle flight management functions:                      //////
#     //////                     (1) core data conversions and monitoring                     //////
#     //////                                                                                  //////
#     //////     This file started as hacking, cutting pasting, spit, chewing gum, bandaid    //////
#     //////     and bailing wire rework of the FlightGear UFO files                          //////
#     //////     version 0.1 released 2006-10-24                                              //////
#     //////     by Philip Cobbin                                                             //////
#     //////                                                                                  //////
#     //////     location: /Flightgear/data/Aircraft/OpenEagle/OpenEagle.nas                  //////
#     //////                                                                                  //////
#     //////                          *****NOTICE*****                                        //////
#     //////                                                                                  //////
#     //////    This program is free software; you can redistribute it and/or modify          //////
#     //////    the Free Software Foundation; either version 2 of the License, or             //////
#     //////    (at your option) any later version.                                           //////
#     //////                                                                                  //////
#     //////    This program is distributed in the hope that it will be useful,               //////
#     //////    but WITHOUT ANY WARRANTY; without even the implied warranty of                //////
#     //////    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 //////
#     //////    GNU General Public License for more details.                                  //////
#     //////                                                                                  //////
#     //////    You should have received a copy of the GNU General Public License             //////
#     //////    along with this program; if not, write to the Free Software                   //////
#     //////    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA      //////
#     //////                                                                                  //////
#     //////    Philip Cobbin; AKA Sierra Simulations & Software can be reached at:           //////
#     //////    499 Grafton Turnpike, Canaan, New Hampshire, U.S.A 03741                      //////
#     //////    Website:  http://www.cobbin.com             e-mail:  cobbin@cobbin.com        //////
#     //////////////////////////////////////////////////////////////////////////////////////////////
####################################################################################################


#################################################################### Open Eagle Nasal Routines ###########################################################

#  ///Density Altitude
#  double temp_C = (5.9/9.0)*(OpenEagleExt.outside_air_temp_degf-32.0);
#  OpenEagleExt.COMPdensity_altitude = OpenEagleExt.G5pressure_alt_ft + 120.0*(temp_C - (15.0 -1.98*(OpenEagleExt.G5pressure_alt_ft/1000.00)));
var PollDensity_Altitude = func {
  outside_air_temp_degf = getprop("/OpenEagle/temperature/outside-air-temp-degf");
  temp_C = (5.9/9.0)*(outside_air_temp_degf - 32.0);
  pressure_alt_ft = getprop("/instrumentation/altimeter/pressure-alt-ft");
  density_altitude = pressure_alt_ft + 120*(temp_C - (15.0 - 1.98*(pressure_alt_ft/1000.0)));
  setprop("/OpenEagle/altitude/density-altitude",density_altitude);
}

PollDensity_AltitudeTimer = maketimer(0.1,PollDensity_Altitude);
PollDensity_AltitudeTimer.start();

var PollCG = func {
  bg_arm = getprop("/OpenEagle/weight_and_balance/baggage_arm");
  bg_wt = getprop("/OpenEagle/weight_and_balance/baggage_wt");
  bg_mom = bg_arm*bg_wt;


  cr_arm = getprop("/OpenEagle/weight_and_balance/crew_arm");
  cr_wt = getprop("/OpenEagle/weight_and_balance/crew_wt");
  cr_mom = cr_arm*cr_wt;


  fl_arm = getprop("/OpenEagle/weight_and_balance/fuel_arm");
  fl_gal = getprop("/OpenEagle/weight_and_balance/fuel_gallons");
  fl_wt = fl_gal*6;
  fl_mom = fl_arm*fl_wt;


  e_wt = getprop("/OpenEagle/weight_and_balance/empty_wt");
  e_mom = getprop("/OpenEagle/weight_and_balance/empty_moment");

  t_wt = e_wt+bg_wt+cr_wt+fl_wt;
  t_mom = bg_mom+cr_mom+fl_mom+e_mom;
  t_arm = t_mom/t_wt;

  setprop("/OpenEagle/weight_and_balance/baggage_moment",bg_mom);
  setprop("/OpenEagle/weight_and_balance/crew_moment",cr_mom);
  setprop("/OpenEagle/weight_and_balance/fuel_moment",fl_mom);
  setprop("/OpenEagle/weight_and_balance/fuel_wt",fl_wt);
  setprop("/OpenEagle/weight_and_balance/total_wt",t_wt);
  setprop("/OpenEagle/weight_and_balance/total_moment",t_mom);
  setprop("/OpenEagle/weight_and_balance/total_arm",t_arm);


}
PollCGTimer = maketimer(0.1,PollCG);
PollCGTimer.start();

var PollPitch = func {
  val = getprop("/orientation/pitch-deg");
  setprop("OpenEagle/orientation/pitch-deg",val);
}

PollPitchTimer  =maketimer(0.1,PollPitch);
PollPitchTimer.start();

var PollHeading = func {
  val = getprop("/orientation/heading-magnetic-deg");
  setprop("OpenEagle/orientation/heading-magnetic-deg",val);
}
PollHeadingTimer  =maketimer(0.1,PollHeading);
PollHeadingTimer.start();

var PollAirspeed = func {
  val = getprop("/velocities/airspeed-kt");
  setprop("OpenEagle/velocities/airspeed-kt",val);
}
PollAirspeedTimer  =maketimer(0.1,PollAirspeed);
PollAirspeedTimer.start();


var PollAutopilot = func {
  route_manager_active = getprop("/autopilot/route-manager/active");
  if (route_manager_active) {
    autopilotTdeg = getprop("/autopilot/settings/true-heading-deg");
    if (autopilotTdeg != nil) {
      Tdeg = getprop("orientation/true-heading-deg");
      if (Tdeg != nil) {
        #print("Tdeg "); print(Tdeg);
        delta = autopilotTdeg-Tdeg;
      #  print("autopilot:"); print(delta);
        setprop("OpenEagle/autopilot/move_reticle_deg", delta);
      #  print("move_reticle_deg");
      #  print(delta);
        if (abs(delta) < 30) {
  #        print("move_reticle 1");
          setprop("OpenEagle/autopilot/move_reticle",1.0);
        }
        else {
   #       print("move_reticle 0");
          setprop("OpenEagle/autopilot/move_reticle",0.0);
        }
      }
      #  else {
      #    print("Tdeg is nil?");
      #  }
    }
  }
  else {
   # print("route-manager is not active");
    setprop("OpenEagle/autopilot/move_reticle",0.0);
  }

}

PollAutopilotTimer = maketimer(0.1,PollAutopilot);
PollAutopilotTimer.start();



#mt_loop_exampleTimer = maketimer(0.25, mt_loop_example);
#mt_loop_exampleTimer.simulatedTime = 1; # use simulated time, as maketimer defaults to using wallclock time and continues during pause.
#mt_loop_exampleTimer.start();


#setprop("OpenEagle/local-fov",1.0);
#setprop("OpenEagle/flight-mode",0);

#setprop("OpenEagle/selector",0);
#setprop("OpenEagle/selector-visible",1);

#setprop("OpenEagle/selector-up",0);
#setprop("OpenEagle/selector-down",0);
#setprop("OpenEagle/selector-toggle",1);
#setprop("OpenEagle/selector-indicator-x",0.0);
#setprop("OpenEagle/selector-indicator-y",0.0);

#setprop("OpenEagle/heading-bug",0);
#setprop("OpenEagle/heading-ccw",0);
#setprop("OpenEagle/heading-cw",0);

#setprop("OpenEagle/terrain-ft",0);
setprop("OpenEagle/vsi-fpm",0);

setlistener("/engines/engine/fuel-pressure-psi", func {
  val = getprop("/engines/engine/fuel-pressure-psi");
  setprop("/engines/engine/fuel-pressure-psi",setDoubleValue(val));
  val += 0.5;
  setprop("/engines/engine/fuel-pressure-psi_rounded",setDoubleValue(val));
  });

setlistener("/engines/engine/oil-pressure-psi", func {
  val = getprop("/engines/engine/oil-pressure-psi");
  val += 0.5;
  setprop("/engines/engine/oil-pressure-psi_rounded",val);
});

setlistener("/engine/engine/oil_temperature-degf", func {
  val = getprop("/engine/engine/oil-temperature-degf");
  setprop("/engine/engine/oil-temperature-degf",setDoubleValue(val));
  });

##
# Handler.  Step to the next view.
#
OEstepView = func {
    curr = getprop("/sim/current-view/view-number");
    views = props.globals.getNode("/sim").getChildren("view");
    curr = curr + 1; #arg[0];
    if   (curr < 0)            { curr = 0; }
    elsif(curr > 3) { curr = 0; }
    setprop("/sim/current-view/view-number", curr);
    if (curr != 1) {
      zoffsetm = getprop("/sim/view/config/z-offset-m");
      fov = getprop("/sim/view/config/default-field-of-view-deg");

    }
    else {
      zoffsetm = 1.25;
      fov = 120;
    }
    setprop("/sim/current-view/field-of-view",fov);
    setprop("/sim/current-view/z-offset-m",zoffsetm);
    # And pop up a nice reminder
    gui.popupTip(views[curr].getNode("name").getValue());
    print("curr ="); print(curr);
}

# OpenEagle hacks of flightgear view.nas file to strictly regulate display of OpenEagle's three views only.  Else you get a Langoliers problem 
# your out the window getting munched till it's just sky blue.... Langoliers as in the Stephen King book/movie....

#
# This is a neat trick.  We want these globals to be initialized at
# startup, but there is no guarantee that the props.nas module will be
# loaded yet when we are run.  So set the values to nil at startup (so
# that there is a value in the lexical environment -- otherwise
# assigning them in INIT() will only make local variables),
# and then assign them from inside a timer that we set to run
# immediately *after* startup.
#
# Nifty hacks notwithstanding, this really isn't the right way to do
# this.  There ought to be an "import" mechanism we can use to resolve
# dependencies between modules.
#
OEfovProp = nil;
OEINIT = func {
    OEfovProp = props.globals.getNode("/sim/current-view/field-of-view");
}
settimer(OEINIT, 0);
# Dynamically calculate limits so that it takes STEPS iterations to
# traverse the whole range, the maximum FOV is fixed at 120 degrees,
# and the minimum corresponds to normal maximum human visual acuity
# (~1 arc minute of resolution, although apparently people vary widely
# in this ability).  Quick derivation of the math:
#
#   mul^steps = max/min
#   steps * ln(mul) = ln(max/min)
#   mul = exp(ln(max/min) / steps)
STEPS = 40;
ACUITY = 1/60; # Maximum angle subtended by one pixel (== 1 arc minute)
max = min = mul = 0;
calcMul = func {
    max = 120; # Fixed at 120 degrees
    min = getprop("/sim/startup/xsize") * ACUITY;
    mul = math.exp(math.ln(max/min) / STEPS);
}

##
# Hackish round-to-one-decimal-place function.  Nasal needs a
# sprintf() interface, or something similar...
#
OEformat = func {
    val = int(arg[0]);
    frac = int(10 * (arg[0] - val) + 0.5);
    return val ~ "." ~ substr("" ~ frac, 0, 1);
}

##
# Handler.  Increase FOV by one step
#
OEincrease = func {
    fov = getprop("/sim/view/config/default-field-of-view-deg");
    fov +=5.0;
    printf("fov ",fov);
    if (fov>160.0) return;
    val=fov;
    setprop("/sim/view/config/default-field-of-view-deg",fov);
    OEfovProp.setDoubleValue(val);
    msg = "FOV: " ~ OEformat(val);
    gui.popupTip(msg);
    return;
# calcMul();
    val = OEfovProp.getValue() * mul;
    if(val == max) { return; }
    if(val > max) { val = max }
#open eagle hacking
    local_fov = getprop("/OpenEagle/local-fov");
    if (local_fov !=nil) {
      if (local_fov>0) {
        r2d = 57.2958;
        d2r =  0.01745;
        k = 0.75;
        m = k/(  math.sin(val*d2r/2.0)/ math.cos(val*d2r/2.0)        );
        setprop("/sim/current-view/z-offset-m[0]",m);
      }
    }
#open eagle hacking
    OEfovProp.setDoubleValue(val);
    gui.popupTip("FOV: " ~ OEformat(val));
}

##
# Handler.  Decrease FOV by one step
#
OEdecrease = func {
    fov = getprop("/sim/view/config/default-field-of-view-deg");
    fov -=5.0;
    printf("fov ",fov);
    if (fov<45.0) return;
    val=fov;
    setprop("/sim/view/config/default-field-of-view-deg",fov);
    OEfovProp.setDoubleValue(val);
    msg = "FOV: " ~ OEformat(val);
    gui.popupTip(msg);

#    m=0;
#    getprop("/sim/current-view/z-offset-m[0]",m);
#    printf("m ",m);
#    m+=0.1;
#    setprop("/sim/current-view/z-offset-m[0]",m);
    return;
   # calcMul();
    val = OEfovProp.getValue() / mul;
    msg = "FOV: " ~ OEformat(val);
    if(val < min) { val=min; }
#open eagle hacking
    local_fov = getprop("/OpenEagle/local-fov");
    if (local_fov !=nil) {
      if (local_fov>0) {
        r2d = 57.2958;
        d2r =  0.01745;
        k = 0.75;
        print("val ",val);
        m = k/(  math.sin(val*d2r/2.0)/ math.cos(val*d2r/2.0)        );
        setprop("/sim/current-view/z-offset-m[0]",m);
      }
    }
#open eagle hacking
    OEfovProp.setDoubleValue(val);
    gui.popupTip(msg);
}


OEHeadingBugInc = func {
#printf("OEHeadingBugIncgot called");
  bug = getprop("OpenEagle/heading-bug");
  if (bug != nil) {
    bug +=1.0;
    while (bug >360) bug -=360;
    while (bug < 0 ) bug +=360;
    setprop("OpenEagle/heading-bug",bug);
    setprop("autopilot/settings/true-heading-deg",bug);
    print("bug "); print(bug);
  }
  else {
    setprop("OpenEagle/heading-bug",0);
    setprop("autopilot/settings/true-heading-deg",0);
  }
# printf("returned?");
}
OEHeadingBugInc();

OEHeadingBugDec = func {
#  printf("OEHeadingBugDec got called");
  bug = getprop("OpenEagle/heading-bug");
  if (bug != nil) {
    bug -=1.0;
    while (bug >360) bug -=360;
    while (bug < 0 ) bug +=360;
    setprop("OpenEagle/heading-bug",bug);
    setprop("autopilot/settings/true-heading-deg",bug);
    print("bug "); print(bug);
    }
  else {
    setprop("OpenEagle/heading-bug",0);
    setprop("autopilot/settings/true-heading-deg",0);
  }
#  printf("returned?");
}

OEHeadingBugInc();


monitor_vsi = func {
  vsi_fps = getprop("/velocities/vertical-speed-fps");
  vsi_fps = getprop("/velocities/speed-down-fps");
  if (vsi_fps!=nil) {
    vsi_fpm = getprop("/OpenEagle/vsi-fpm");
    if (vsi_fpm !=nil) {
      setprop("OpenEagle/vsi-fpm",vsi_fps*-60.0);
#      setprop("OpenEagle/vsi-fpm",vsi_fps*60.0);
    }
  } 
  settimer(monitor_vsi,0);
}
monitor_vsi ();

monitor_gps_gs = func {
  gps_gs_kt = getprop("/instrumentation/gps/indicated-ground-speed-kt");
  ##if (gps_gs_kt!=nil) {
    gps_gs_mph = gps_gs_kt*1.15;
    setprop("OpenEagle/gps/indicated-ground-speed-mph",gps_gs_mph);
 ## } 
  settimer(monitor_gps_gs,0.1);
}
monitor_gps_gs ();

abs = func { if(arg[0] < 0) { -arg[0] } else { arg[0] } }

fix_lat_long = func {
  latitude  = getprop("/position/latitude-deg");
  longitude = getprop("/position/longitude-deg");

  setprop("/OpenEagle/latitude-deg",latitude);
  setprop("/OpenEagle/longitude-deg",longitude);  
# lat = 35.12345678 
  lat1 = int(latitude/10);   #3
  lat2 = int(latitude-lat1*10); #5
#  lat3 = int latitude'
 
#  ns=3; #n;
  ns=1; #s;
#  ew=2; #e
  ew=4; #w
 
  if (latitude>0) { ns=3; } 
  if (longitude>0) {ew=2; } 
   
  latitude = abs(latitude);
  longitude = abs(longitude);
#  lat  = int(latitude);
#  long = int(longitude);

  lat_min= (latitude-int(latitude))*60.0;
  long_min = (longitude-int(longitude))*60.0;

  lat_rem = (lat_min-int(lat_min))*1000.0;
  long_rem = (long_min-int(long_min))*1000.0;

  lat_min=int(lat_min);
  long_min=int(long_min);

  setprop("/OpenEagle/ns",ns);
  setprop("/OpenEagle/ew",ew);
  setprop("/OpenEagle/latitude",latitude);
  setprop("/OpenEagle/longitude",longitude);
  setprop("/OpenEagle/lat-min",lat_min);
  setprop("/OpenEagle/long-min",long_min);
  setprop("/OpenEagle/lat-rem",lat_rem);
  setprop("/OpenEagle/long-rem",long_rem);

  settimer(fix_lat_long, 0);


}

fix_lat_long();


fix_ground_proximity = func {  # who's the leader of the pack that's made for you and me... grr on factor not working?
#  print("fix_ground_proximity entry");
  alt = props.Node.new();
  alt    = getprop("/position/altitude-ft");
  ground = getprop("/position/ground-elev-ft");
  if (alt !=nil) {
#   print("  alt ",alt);
    if (ground != nil) {
 #     print("  ground ",ground);
      agl = alt - ground;
  #    print("                   agl is ",agl);
 #     ground = ground-1000;
      setprop("/position/altitude-agl-ft",agl);
      setprop("/position/ground_prosimity",agl);
    }
  }  
#  print("fix_ground_proximity exit");
  settimer(fix_ground_proximity, 0);
 
}

fix_ground_proximity ();

#monitor_selector = func {

 # print("monitor_selector entry");
##  flightmode = props.Node.new();
#  selector_visible = getprop("/OpenEagle/selector-visible");
#  if (selector_visible !=nil) {
#    if (selector_visible>0) {

#      selector = getprop("/OpenEagle/selector");
 
 #     if (selector !=nil) {
 #       #print("selector = ",selector);
 #       setprop("OpenEagle/selector-indicator-y",selector*(-0.0164)+0.198);
 #       setprop("OpenEagle/selector-indicator-x",-0.045);
#      }
#      else print("selector is nil");
#    }
#    #else print("selector_visible <=0");
#  }
#  else print("selector_visible is nil");
#  settimer(monitor_selector,0);
#}

#monitor_selector ();

#monitor_selector_up = func {
#  selector_up = getprop("/OpenEagle/selector-up");
#  if (selector_up !=nil) {
#    if (selector_up>0) {
#      setprop("/OpenEagle/selector-up",0);
#      selection = getprop("/OpenEagle/selector");
#      if (selection !=nil) {
#        selection = selection + 1;
#        if (selection>26) { selection = 1; }
#        setprop("/OpenEagle/selector",selection);
#      }
#    }
#  }
#  settimer(monitor_selector_up,0);
#}
#monitor_selector_up ();

#monitor_selector_down = func {
#  selector_down = getprop("/OpenEagle/selector-down");
#  if (selector_down !=nil) {
#    if (selector_down>0) {
#      setprop("/OpenEagle/selector-down",0);
#      selection = getprop("/OpenEagle/selector");
#      if (selection !=nil) {
#        selection = selection - 1;
#        if (selection<1) {selection = 26; }
#        setprop("/OpenEagle/selector",selection);
#      }
#    }
#  }
#  settimer(monitor_selector_down,0);
#}
#monitor_selector_down ();


#monitor_selector_toggle = func {
#  selector_visible = getprop("/OpenEagle/selector-visible");
#  if (selector_visible !=nil) {
#    if (selector_visible>0) {
#      selector_toggle = getprop("/OpenEagle/selector-toggle");
#      if (selector_toggle !=nil) {
#        if (selector_toggle>0) {
#          setprop("/OpenEagle/selector-toggle",0);
#          selection = getprop("/OpenEagle/selector");
#          if (selection !=nil) {
#            if (selection >0) {
#              print("short selection = ",selection);
#              print("x[selection] = ",x[selection]);
#              current = getprop(x[selection]);
#              print("selection", x[selection]);
#              if (current!=nil) {
#                if (current>0) { 
#                  current=0;
#                }
#                else {
#                  current=1;
#                }
#                setprop(x[selection],current);
#              }
#              else printf("did not exist");
#            }
#          } 
#        }
#      }
#    }
#  }
#  setprop("/OpenEagle/selector-toggle",0);
#  settimer(monitor_selector_toggle, 0);
#}

#monitor_selector_toggle ();



