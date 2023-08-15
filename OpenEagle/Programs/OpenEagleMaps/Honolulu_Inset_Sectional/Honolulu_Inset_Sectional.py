import processing
processing.run('qgis:tilesxyzdirectory', { 'DPI' : 96, 'EXTENT' : '-158.697318015,-157.154987678,20.712523881,21.641905146 [EPSG:4326]', 'METATILESIZE' : 4, 'OUTPUT_DIRECTORY' : '.', 'QUALITY' : 75, 'TILE_FORMAT' : 0, 'TILE_HEIGHT' : 256, 'TILE_WIDTH' : 256, 'TMS_CONVENTION' : False, 'ZOOM_MAX' : 13, 'ZOOM_MIN' : 8 })

import os
os._exit(0)
