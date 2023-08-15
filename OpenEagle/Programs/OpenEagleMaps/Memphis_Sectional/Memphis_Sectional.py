import processing
processing.run('qgis:tilesxyzdirectory', { 'DPI' : 96, 'EXTENT' : '-96.427153377,-87.551078173,31.219147955,36.567715510 [EPSG:4326]', 'METATILESIZE' : 4, 'OUTPUT_DIRECTORY' : '.', 'QUALITY' : 75, 'TILE_FORMAT' : 0, 'TILE_HEIGHT' : 256, 'TILE_WIDTH' : 256, 'TMS_CONVENTION' : False, 'ZOOM_MAX' : 13, 'ZOOM_MIN' : 8 })

import os
os._exit(0)
