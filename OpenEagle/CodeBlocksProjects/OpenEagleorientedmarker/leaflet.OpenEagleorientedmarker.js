/*
 Leaflet.orientedmarker, Provides dynamic orientation functionality for Leaflet markers.
 https://github.com/gismartwaredev/leaflet.orientedMarker
 (c) 2015, Alexandre DAVID (http://github.com/alexandreDavid), GiSmartware
*/
/*
 Modified version of orientedmarker to fix mis-locating marker position on leaflet 1.5.1 maps for the OpenEagle project
 released under same license as the leaflet.orientedmarker
*/
(function (window, document, undefined) {
    L.OrientedMarker = L.Marker.extend({
        options: {
            angle: 0,
            orientationLineColor: 'red',
            orientationLineWeight: 5,
            orientationLineOpacity: 0.8
        },
        isOriented: true,
        _setPos: function (pos) {
            L.Marker.prototype._setPos.call(this, pos);
            this._initIconStyle = this._icon.style[L.DomUtil.TRANSFORM] + '';
            this._updateImg();
        },
        _updateImg: function() {
               console. log('_updateImg():');   
            var a = this.options.icon.options.iconAnchor,
            i, s;
            if (this._icon) {
              i = this._icon;
                s = this.options.icon.options.iconSize;
              console. log('  a',a,' i',i,' s ',s);
                this._orienteIcon(i, a, s)
              console. log('post _orientIcon call:  a',a,' i',i,' s ',s);
            }
            if (this._shadow) {
                s = this.options.icon.options.shadowSize;
                i = this._shadow;
                this._orienteIcon(i, a, s)
            }
        },
        _orienteIcon: function (i, a, s) {
                        console.log('_orientIcon ( i',i,', a',a,',s ',s,')');  
            if (!s) {
                        /// console. log('_orientIcon 2 b4 rotate');  
              i.style[L.DomUtil.TRANSFORM] = this._initIconStyle + ' rotate(' + this.options.angle + 'deg)';
     //                                  console. log('_orientIcon 3 after rotate b4 return',this.options.angle);  
                return;
            }
    ///     /// console. log('_orientIcon 4');      
      //    console. log('  L.point(s)',L.point(s));
      //    console. log('  L.point(a)',L.point(a));
            a = L.point(s).divideBy(2)._subtract(L.point(a));
     //     console. log('  a',a);
          var H = L.point(s);
          var hx =H.x ;
          var hy =H.y;
          var x;
          var y;
          console.log('   hx',hx,'   hy',hy);
            x = Math.sin((this.options.angle - 75.0)*Math.PI / 180)*hx/2.0;
            y = Math.sin((this.options.angle - 165.0)*Math.PI / 180)*hy/2.0;
            console.log('  x ',x,'  y',y);
            var transform = '';
            transform += ' translate(' + x + 'px, ' + y + 'px)';
//            transform += ' translate(' + -a.x + 'px, ' + -a.y + 'px)';
//            transform += ' translate(' + '-25px, ' + '-4px)';  /// heading =  0 50x50 icon
//            transform += ' translate(' + ' -22px, ' + '-14px)';  /// heading =   15 50x50 icon
//            transform += ' translate(' + '-18px, ' + '-20px)';   /// heading =  30 50x50 icon
//            transform += ' translate(' + '-16px, ' + '-21px)';  /// heading =  45 50x50 icon
//            transform += ' translate(' + '-6px, ' + '-28px)';  /// heading =  60 50x50 icon
//            transform += ' translate(' + '0px, ' + '-28px)';  /// heading =  75 50x50 icon
//            transform += ' translate(' + '10px, ' + '-26px)';   /// heading = 90 50x50 icon
//            transform += ' translate(' + '18px, ' + '-21px)';   /// heading =  105 50x50 icon
//               transform += ' translate(' + '19px, ' + '-19px)';   /// heading =  120 50x50 icon
//            transform += ' translate(' + ' 22px, ' + '-14px)'; /// heading =  135 50x50 icon
//            transform += ' translate(' + ' 26px, ' + '-4px)'; /// heading =  150 50x50 icon
//            transform += ' translate(' + ' 27px, ' + '0px)'; /// heading =  165 50x50 icon
//            transform += ' translate(' + '26px, ' + '4px)'   /// heading =180 50x50 icon
//            transform += ' translate(' + '22px, ' + '14px)'   /// heading =195 50x50 icon
//            transform += ' translate(' + '19px, ' + '19px)'   /// heading =210 50x50 icon
//            transform += ' translate(' + '14px, ' + '21px)'   /// heading =225 50x50 icon
//            transform += ' translate(' + '5px, ' + '28px)'   /// heading =240 50x50 icon
//            transform += ' translate(' + '0px, ' + '28px)'   /// heading =255 50x50 icon
//            transform += ' translate(' + '-6px, ' + '25px)';   /// heading =270 50x50 icon
//            transform += ' translate(' + '-14px, ' + '21px)'   /// heading =285 50x50 icon
//            transform += ' translate(' + '-18px, ' + '20px)';   /// heading =300 50x50 icon
//            transform += ' translate(' + '-22px, ' + '12px)';   /// heading =315 50x50 icon
//            transform += ' translate(' + '-26px, ' + '6px)';   /// heading =330 50x50 icon
          //  transform += ' translate(' + '-24px, ' + '-6px)';   /// heading =330 50x50 icon
            transform += ' rotate(' + this.options.angle + 'deg)';
//            transform += ' translate(' + a.x + 'px, ' + a.y + 'px)';
//            transform += ' translate(' + '0px, ' + a.y + 'px)';
         /// console. log('_orientIcon 5');  
            i.style[L.DomUtil.TRANSFORM] = this._initIconStyle +' ' +transform;
                                     console. log('_orientIcon 6 transform:',   transform);  
                                     console.log('end of _orientIcon');
        },
        onRemove: function (map) {
            this._orientationLine.onRemove(this._map);
            this._orientationCircle.onRemove(this._map);
            L.Marker.prototype.onRemove.call(this, map);
            return this;
        },
        update: function () {
            L.Marker.prototype.update.call(this);
            if (this._orientationLine) {
                this.activateOrientation();
            }
            return this;
        },
        activateOrientation: function() {
            var that = this;
            that._setOrientationDirectionLine();
            that._orientationMouseDown = false;
            that._orientationLine.addTo(that._map);
            that._orientationCircle.addTo(that._map);
            that._orientationLine.on('mousedown', beginOrientation);
            that._orientationCircle.on('mousedown', beginOrientation);
            that._map.on('mousemove', moveOrientation);
            document.onmouseup = stopOrientation;
            // Mobile controls
         ///// console. log('begin Orientation 1');
/**            that._orientationLine._container.ontouchstart = beginOrientation;
            that._orientationCircle._container.ontouchstart = beginOrientation;
            that._orientationCircle._container.ontouchmove = mobileMoveOrientation;
            that._orientationCircle._container.ontouchmove = mobileMoveOrientation;
            that._orientationCircle._container.ontouchend = stopOrientation;
            that._orientationCircle._container.ontouchend = stopOrientation;**/
         ///// console. log('begin Orientation 2');
            function beginOrientation() {
           //            /// console. log('begin Orientation 3');
                that._savedDragging = that._map.dragging;
                that._savedMouseUp = document.onmouseup;
        ///        that._map.dragging.disable();
                that._map.dragging = false;
                that._orientationMouseDown = true;
            }
            function mobileMoveOrientation(e) {
             ///          /// console. log('begin Orientation 4');
                if (that._orientationMouseDown) {
                    var touches = e.changedTouches,
                        lastTouch = touches[touches.length - 1];
                    newLatLng = that._map.layerPointToLatLng(
                        that._map.mouseEventToLayerPoint({clientX: lastTouch.pageX, clientY: lastTouch.pageY})
                    );
                    moveOrientation({latlng: newLatLng});
                }
            }
            function moveOrientation(e) {
                //       /// console. log('begin Orientation 5');
                if (that._orientationMouseDown) {
                    var pointB = new L.LatLng(e.latlng.lat, e.latlng.lng);
                    that._orientationLine.setLatLngs([that._latlng, pointB]);
                    that._orientationCircle.setLatLng(pointB);
                    that._setAngle();
                }
            }
            function stopOrientation() {
                  //     /// console. log('begin Orientation 6');
                if (that._orientationMouseDown) {
                    that._orientationMouseDown = false;
///                    that._map.dragging.enable();
                    that._map.dragging = true;
                    that._setAngle();
                }
            }
            return that;
        },
        _setOrientationDirectionLine: function() {
      //             /// console. log(' _setOrientationDirectionLine 1');
            if (this._orientationLine) {
                this._map.removeLayer(this._orientationLine);
                this._map.removeLayer(this._orientationCircle);
            }
        // /// console. log(' _setOrientationDirectionLine 2');
            var transformation = new L.Transformation(
                    1, Math.sin(this.options.angle*Math.PI / 180)*100,
                    1, Math.cos(this.options.angle*Math.PI / 180)*-100
                ),
                pointB = this._map.layerPointToLatLng(
                    transformation.transform(this._map.latLngToLayerPoint(this._latlng))
                );
             /// console. log(' _setOrientationDirectionLine 3 transformation',transformation,' pointB ',pointB);
            var pointList = [this._latlng, pointB];
            this._orientationLine = new L.Polyline(pointList, {
                color: this.options.orientationLineColor,
                weight: this.options.orientationLineWeight,
                opacity: this.options.orientationLineOpacity,
                smoothFactor: 1
            });
         ///// console. log(' _setOrientationDirectionLine 4');
            this._orientationCircle = new L.circleMarker(pointB, {
                radius: this.options.orientationLineWeight*2,
                color: this.options.orientationLineColor,
                fillColor: this.options.orientationLineColor,
                fillOpacity: this.options.orientationLineOpacity
            });
        },
        _orientationMouseDown: false,
        _savedDragging: false,
        _savedMouseUp: false,
        validateOrientation: function(callback) {
        //  console.log(' validateOrientation 1');
            if (!this._orientationLine) {
                return this;
            }
        //  console.log(' validateOrientation 2');
            this._map.dragging = this._savedDragging;
            document.onmouseup = this._savedMouseUp;
            this._orientationLine.onRemove(this._map);
            this._orientationCircle.onRemove(this._map);
            this._orientationLine = false;
            this._orientationCircle = false;
          //         /// console. log(' validateOrientation 3');
            return this;
        },
        _setAngle: function() {
            //     /// console. log(' _setAngle 1');
            var A = this._orientationLine._parts[0][0],
                B = this._orientationLine._parts[0][1];
                  console. log(' _setAngle  A',A,' B',B);
                this.options.angle = (Math.atan2(0,1) - Math.atan2((B.x - A.x),(B.y - A.y)))*180/Math.PI+180;
                  console. log(' _setAngle this.options.angle',this.options.angle);
                this._updateImg();
        },
        _initIconStyle: false,
        _orientationLine: false,
        _orientationCircle: false
    });
    L.orientedMarker = function (pos, options) {
        return new L.OrientedMarker(pos, options);
    };
}(window, document));
