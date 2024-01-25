import { Routes } from '@angular/router';

export const routes: Routes = [
  {
    path: '',
    pathMatch: 'full',
    loadComponent: () =>
      import('./components/welcome/welcome.component').then(
        (mod) => mod.WelcomeComponent
      ),
  },
  {
    path: 'dariel',
    loadComponent: () =>
      import('./components/experience/detailed/dariel/dariel.component').then(
        (mod) => mod.DarielComponent
      ),
  },
];