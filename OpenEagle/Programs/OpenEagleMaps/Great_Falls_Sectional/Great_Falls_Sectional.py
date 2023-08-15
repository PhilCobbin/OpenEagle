import processing
processing.run('qgis:tilesxyzdirectory', { 'DPI' : 96, 'EXTENT' : '-118.846904679,-108.008541389,43.409551447,49.940559455 [EPSG:4326]', 'METATILESIZE' : 4, 'OUTPUT_DIRECTORY' : '.', 'QUALITY' : 75, 'TILE_FORMAT' : 0, 'TILE_HEIGHT' : 256, 'TILE_WIDTH' : 256, 'TMS_CONVENTION' : False, 'ZOOM_MAX' : 13, 'ZOOM_MIN' : 8 })

import os
os._exit(0)
