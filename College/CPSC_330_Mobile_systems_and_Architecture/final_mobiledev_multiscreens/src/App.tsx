/* Author:         Daniel Tripoli                             */
/* Major:          Computer Science                           */
/* Creation Date:  May 6, 2026                                */
/* Due Date:       May 8, 2026                                */
/* Course: CPSC    310 010                                    */
/* Professor Name: Prof. Wang                                 */
/* Project:        #6                                         */
/* Filename:       App.tsx                                    */
/* Purpose:        Implements running the app as a whole      */

import { Assets as NavigationAssets } from '@react-navigation/elements';
import { Asset } from 'expo-asset';
import * as React from 'react';
import { Navigation } from './navigation';
import {LoginContext} from './navigation/LogInContext'

Asset.loadAsync([
  ...NavigationAssets,
]);

export function App() {

  return (
    <LoginContext>
      <Navigation/>
    </LoginContext>
  )
}
