import numpy as np
from shapely.geometry import Point, Polygon
import os

def random_points_bounds(polygon, number):   
    minx, miny, maxx, maxy = polygon.bounds
    x = np.random.uniform(minx, maxx, number)
    y = np.random.uniform(miny, maxy, number)
    return x, y

import geopandas as gpd

for p in range(50, 1020, 50):

    with open(f"./regular_polygons/{p}.txt") as f:
        lines = f.readlines()
        lines = [line.strip().split(" ") for line in lines]

    polygon = Polygon(map(lambda line: [float(line[0]), float(line[1])], lines))
    points = []
    for line in lines:
        x = float(line[0])
        y = float(line[1])
        points.append((x,y))

    gdf_poly = gpd.GeoDataFrame(index=["myPoly"], geometry=[polygon])
    import pandas as pd
    j=0
    for l in range(1000, 110000, 10000):
        x,y = random_points_bounds(polygon, l)
        df = pd.DataFrame()
        df['points'] = list(zip(x,y))
        df['points'] = df['points'].apply(Point)
        gdf_points = gpd.GeoDataFrame(df, geometry='points')

        Sjoin = gpd.tools.sjoin(gdf_points, gdf_poly, predicate="within", how='left')

        pnts_in_poly = gdf_points[Sjoin.index_right=='myPoly']

        df = pd.DataFrame()
        df['points'] = points
        df['points'] = df['points'].apply(Point)
        gdf_points = gpd.GeoDataFrame(df, geometry='points')

        gdf = pd.concat([gdf_points, pnts_in_poly], ignore_index=True)

        # print(pnts_in_poly.shape[])
        # print(pnts_in_poly)

        if not os.path.exists(f"bc_gift_wrapping/{p}"):
            os.mkdir(f"bc_gift_wrapping/{p}")
        j+=1
        with open(f"bc_gift_wrapping/{p}/{j}", "w") as fout:
            for i in range(gdf.shape[0]):
                fout.write(f"{gdf.iloc[i, 0].x} {gdf.iloc[i, 0].y}\n")



    