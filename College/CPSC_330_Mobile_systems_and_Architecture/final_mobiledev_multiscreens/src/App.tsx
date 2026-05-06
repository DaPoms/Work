import { Assets as NavigationAssets } from '@react-navigation/elements';
import { Asset } from 'expo-asset';
import { createURL } from 'expo-linking';
import * as SplashScreen from 'expo-splash-screen';
import * as React from 'react';
import { Navigation } from './navigation';
import {LoginContext} from './navigation/LogInContext'

Asset.loadAsync([
  ...NavigationAssets,
]);

SplashScreen.preventAutoHideAsync();


export function App() {

  return (
    <LoginContext>
      <Navigation/>
    </LoginContext>
  )
}
