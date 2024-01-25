import { CommonModule } from '@angular/common';
import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-welcome',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './welcome.component.html',
  styleUrl: './welcome.component.css',
})

export class WelcomeComponent implements OnInit {
  currentWord: string = 'A DEVELOPER';
  showSecondWord: boolean = false;

  ngOnInit() {
    setTimeout(() => {
      this.currentWord = 'ANDRE STEYN';
      this.showSecondWord = true;
    }, 3500);
  }
}
