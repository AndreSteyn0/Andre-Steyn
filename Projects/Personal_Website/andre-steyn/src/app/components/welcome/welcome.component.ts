import { CommonModule, ViewportScroller } from '@angular/common';
import { AfterViewInit, Component } from '@angular/core';
import { ScrollService } from '../../services/scroll.service';

@Component({
  selector: 'app-welcome',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './welcome.component.html',
  styleUrl: './welcome.component.css',
})

export class WelcomeComponent {
  constructor(){}
}
