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
