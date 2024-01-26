import { Routes } from '@angular/router';

export const routes: Routes = [
  {
    path: '',
    pathMatch: 'full',
    loadComponent: () =>
      import('./components/main/main.component').then(
        (mod) => mod.MainComponent
      ),
  },
  {
    path: 'dariel',
    loadComponent: () =>
      import('./components/experience/detailed/dariel/dariel.component').then(
        (mod) => mod.DarielComponent
      ),
  },
  {
    path: 'minopex',
    loadComponent: () =>
      import('./components/experience/detailed/minopex/minopex.component').then(
        (mod) => mod.MinopexComponent
      ),
  },
  {
    path: '**',
    redirectTo: ''
  },
];