/* Author:         Daniel Tripoli                             */
/* Major:          Computer Science                           */
/* Creation Date:  May 6, 2026                                */
/* Due Date:       May 8, 2026                                */
/* Course: CPSC    310 010                                    */
/* Professor Name: Prof. Wang                                 */
/* Project:        #6                                         */
/* Filename:       LogInContext.tsx                           */
/* Purpose:        Shares state of log in                     */

import { createContext, useContext, useState, ReactNode } from 'react';

const isLoggedInContext = createContext<{isLoggedIn:boolean, setIsLoggedIn: (value:boolean) => void } | null>(null)

export function LoginContext( {children} : { children: ReactNode }) {
  const [isLoggedIn, setIsLoggedIn] = useState(false);
  
  return (
    <isLoggedInContext.Provider value = {{ isLoggedIn, setIsLoggedIn }}>
      {children}
    </isLoggedInContext.Provider>
  );
}

export function useLogInContext() {
  return useContext(isLoggedInContext);
}
