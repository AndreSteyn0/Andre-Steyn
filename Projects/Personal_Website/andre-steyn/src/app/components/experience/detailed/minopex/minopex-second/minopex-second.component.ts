import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { ScrollService } from '../../../../../services/scroll.service';

@Component({
  selector: 'app-minopex-second',
  standalone: true,
  imports: [],
  templateUrl: './minopex-second.component.html',
  styleUrl: './minopex-second.component.css'
})
export class MinopexSecondComponent {
  constructor(private router: Router, private scrollService: ScrollService) {}

  ngAfterViewInit() {
    this.scrollService.scrollObservable.subscribe((section) => {
      setTimeout(() => {
        this.scrollToElement(section);
      }, 0);
    });
  }

  navigateAndScroll(): void {
    this.scrollService.scrollTo('minopexAnchor');
    this.router.navigate(['']);
  }

  scrollToElement(section: string) {
    document.getElementById(section)?.scrollIntoView({ behavior: 'smooth', inline:'start', block: 'start' });
  }
}
