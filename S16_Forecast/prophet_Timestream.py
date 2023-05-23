#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct  8 17:53:06 2022

@author: vladimir
"""

# %% Importar bibliotecas
import awswrangler as wr
#import boto3 
import pandas as pd
from prophet import Prophet
from datetime import datetime,timedelta

# %% Consultar fuentes en Amazon

#Timestream
query = 'SELECT * FROM "EmbebedCloud"."Axolote_all_devices" WHERE deviceID = \'Axolote_Aldo\' ORDER BY time DESC ' 
df = wr.timestream.query(query)
# %% Preprocesamiento
#La consulta de timestream está en formato 'wide'
#Hay que cambiarla a formato 'Long'
df = df.pivot(index='time', 
                       columns='measure_name', 
                       values= ['measure_value::double','measure_value::varchar']).dropna(axis = 1, thresh = 10)


#Deshacermos de las columnas multinivel
df.columns = df.columns.get_level_values(1)
df = df.drop(columns=["device_Id","lat_deg","lat_long","long_deg","gps_date_time","mac_Id"])

#Formatear columnas con su tipo de dato
df["ligh_adim"] = pd.to_numeric(df["ligh_adim"],errors = "coerce")
df["press_hPa"] = pd.to_numeric(df["press_hPa"],errors = "coerce")
df["temp_C"] = pd.to_numeric(df["temp_C"],errors = "coerce")
df.index = pd.to_datetime(df.index)


# %% Previsualizar

variable = "ligh_adim"
#df.plot(y = "press_hPa", use_index = True)
#Subsetting para tener información manejable
#Resampling para tener una frecuencia de discretización constante
#Rolling para eliminar transiciones de alta frecuencia
df_subset = df[df.index>(datetime.today()-timedelta(days = 8))]
df_resamp = df_subset.resample('10min').mean().interpolate()
df_rolling = df_resamp.rolling(3).mean()

df_subset.plot(y = variable, use_index = True)
df_resamp.plot(y = variable, use_index = True)
df_rolling.plot(y = variable, use_index=True )
# %%Prophet fit
df_prophet = pd.DataFrame()
df_prophet["y"] = df_rolling[variable]
df_prophet["ds"] = df_rolling.index.tz_localize(None)

m = Prophet(changepoint_prior_scale=0.001).fit(df_prophet)
# %% Prophet predictions
future = m.make_future_dataframe(periods=12, freq='H')
fcst = m.predict(future)
fig = m.plot(fcst)
