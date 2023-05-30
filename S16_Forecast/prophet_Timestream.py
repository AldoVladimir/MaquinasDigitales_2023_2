#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct  8 17:53:06 2022

@author: vladimir
"""

# %% Importar bibliotecas
import awswrangler as wr
import pandas as pd
from prophet import Prophet
from datetime import datetime,timedelta

# %% Consultar fuentes en Amazon

#Timestream
# query = """select time,
# 	  measure_value::double as temperatura_c
# from atmosfera_axolote.axolote_oscar_qa
# where measure_name = 'temp_C'
# 	and time between ago(30d) and now()
#order by time desc"""
query = """select time,
	  measure_value::double as temperatura_c
from atmosfera_axolote.axolote_oscar_qa
where measure_name = 'press_hPa'
	and time between ago(30d) and now()
order by time desc"""

df = wr.timestream.query(query)
# %% Previsualizar

#variable = "ligh_adim"
df.plot(y = 1, x = 0, xlim = [datetime(2023,5,22),datetime(2023,5,30)])
#Subsetting para tener información manejable
#Resampling para tener una frecuencia de discretización constante
#Rolling para eliminar transiciones de alta frecuencia
df_subset = df[df.iloc[:,0]>(datetime.today()-timedelta(days = 8))]
df_subset.set_index('time',inplace= True)
df_resamp = df_subset.resample('10min').mean().interpolate()
df_rolling = df_resamp.rolling(5).mean()

df_subset.plot(y = 0, use_index = True)
df_resamp.plot(y = 0, use_index = True)
df_rolling.plot(y = 0, use_index = True )
# %%Prophet fit
df_prophet = pd.DataFrame()
df_prophet["y"] = df_rolling.iloc[:,0]
df_prophet["ds"] = df_rolling.index.tz_localize(None)

m = Prophet(changepoint_prior_scale=0.001).fit(df_prophet)
# %% Prophet predictions
future = m.make_future_dataframe(periods=12, freq='H')
fcst = m.predict(future)
fig = m.plot(fcst)
