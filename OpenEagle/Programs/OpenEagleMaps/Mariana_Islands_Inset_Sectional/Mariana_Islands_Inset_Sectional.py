import processing
processing.run('qgis:tilesxyzdirectory', { 'DPI' : 96, 'EXTENT' : '142.729220122,146.885222413,12.986068858,15.490403093 [EPSG:4326]', 'METATILESIZE' : 4, 'OUTPUT_DIRECTORY' : '.', 'QUALITY' : 75, 'TILE_FORMAT' : 0, 'TILE_HEIGHT' : 256, 'TILE_WIDTH' : 256, 'TMS_CONVENTION' : False, 'ZOOM_MAX' : 13, 'ZOOM_MIN' : 8 })

import os
os._exit(0)
